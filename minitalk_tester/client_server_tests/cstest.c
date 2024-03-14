#include "../minitalk_tester.h"

int check_server_output(char* test)
{
	ssize_t ret = -2;
	int fd1;
	int fnl = 0;
	int lnl = 0;
	char buf[10000];
	printf("hallo\n");
	usleep(10000000);
	fd1 = open(SERTEST, O_RDONLY);
	if (fd1 == -1)
	{
		printf("Error with opening fd for %s in check_server_output function\n", SERVOUT);
		exit(EXIT_FAILURE); 
	}
	while (ret != 0)
	{
		ret = read(fd1, buf, 1000);
		if(ret == -1)
		{
			printf("Error with reading in check_server_output function\n");
			exit(EXIT_FAILURE);
		}
	}
	while(buf[fnl] != '\n')
		fnl++;
	lnl = fnl + 1;
	while(buf[lnl] != '\n')
		lnl++;
	printf("fnl %d lnl %d\n", fnl, lnl);
	buf[lnl] = '\0';
	printf("buf: \n%s\n", buf);
	return(strcmp(test, buf));
}


void get_server_pid(char* pid)
{
	ssize_t ret = -2;
	int fd;
	int len = 0;
	fd = open(SERTEST, O_RDONLY);
	char buf[1];
	int index = 0;
	usleep(10000);
	if (fd == -1)
	{
		printf("Error with opening fd for %s in get_server_pid function\n", SERTEST);
		exit(EXIT_FAILURE); 
	}
	while (ret != 0)
	{
		ret = read(fd, buf, 1);
		printf("%c\n", buf[0]);
		if(ret == -1)
		{
			printf("Error with reading in get_server_pid function\n");
			exit(EXIT_FAILURE);
		}
		pid[index] = buf[0];
		index++;
		len += ret;
	}
	pid[len] = '\0';
}

int start_server(char** envp)
{
	pid_t pid;
	int estatus = -1;
	int wstatus = 0;

	freopen(SERTEST, "a+", stdout);
	pid = fork();
	if(pid == 0)
	{
		estatus = execve("server", (char *[]){NULL}, envp);
		if(estatus == -1)
		{
			printf("Error with execve in start_server function\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		freopen("/dev/tty", "w", stdout);
		waitpid(pid, &wstatus, WNOHANG);
		if(wstatus == 0)
			return(0);
		else
			return(wstatus);
	}
}


int client_server_test(int testnum, char** argv, char** envp)
{
	pid_t pid;
	int estatus = 0;
	int wstatus = -1;
	int sstatus = -1;
	int rstatus = -1;
	char *serverpidstr;

	serverpidstr = malloc(100);
	if(serverpidstr == NULL)
	{
		printf("malloc with serverpidstr went wrong\n");
		exit(EXIT_FAILURE);
	}
	if(start_server(envp))
	{
		printf("Server did not start\n");
		exit(EXIT_FAILURE);
	}
	get_server_pid(serverpidstr);
	if(!serverpidstr)
	{
		printf("Failed to get pid of server\n");
		exit(EXIT_FAILURE);
	}
	argv[1] = serverpidstr; 
	pid = fork();
	freopen(SERVOUT, "a+", stdout);
	if(pid == 0)
	{
		estatus = execve("client", argv, envp);
		freopen("/dev/tty", "w", stdout);
		if(estatus == -1)
		{
			printf("Error with execve in client_tester function\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &wstatus, 0);
		freopen("/dev/tty", "w", stdout);
		printf("hello\n");
		sstatus = check_server_output(argv[2]);
	}
	freopen("/dev/tty", "w", stdout);
	if(wstatus != 0 || sstatus != 0)
	{
		printf(RED "%d FAIL " RESET, testnum);
		freopen(SERClILOGS, "a+", stdout);
		printf("testnum: %d\n", testnum);
		printf("test case: %s", argv[2]);
		printf("returned process status (wstatus): %d\n", wstatus);
		printf("returned server check (sstatus): %d\n", sstatus);
		printf("-------------------------\n");
		freopen("/dev/tty", "w", stdout);
	}
	if(wstatus == 0 && sstatus == 0)
	{
		printf(GRN "%d OK " RESET, testnum);
		rstatus = 0;
	}
	return(rstatus);
}

void client_server_tests(char** envp)
{
	int status = 0;
	int testnum = 0;
	printf(YEL "Client - Server\n" RESET);
	status += client_server_test(++testnum, (char *[]){"client", "", "lol", NULL}, envp);
	printf("\n");
	if (status != 0)
		printf("There was something wrong, check combination of %s and %s\n", CLIENTLOGS, ClIOUTLOGS);
}

