#include "../minitalk_tester.h"


void kill_server(char ** argv)
{
	int call = -1;

	freopen(SERTEST, "a+", stdout);
	call = kill(atoi(argv[1]), 0);
	if(call == -1)
	{
		printf("Error with checking pid of server in kill_server\n");
		exit(EXIT_FAILURE);
	}
	if(call == 0)
	{
		call = kill(atoi(argv[1]), 9);
		if(call == -1)
		{
			printf("Error with kill server process in kill_server function\n");
			exit(EXIT_FAILURE);
		}
	}	
}


int check_server_output(char* test)
{
	ssize_t ret = -2;
	int fd1;
	int fnl = 0;
	int lnl = 0;
	int retint = -1;
	char buf[10000];
	usleep(100);
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
	buf[lnl] = '\0';
	strlcpy(buf, buf + (fnl + 1), lnl - fnl);
	retint = strcmp(test, buf); 
	if(retint)
	{
		freopen(SERClILOGS, "a+", stdout);
		
		printf("test: %s\n", test); 
		printf("buf : %s\n", buf); 
		freopen("/dev/tty", "w", stdout);
	}
	return(retint);
}


void get_server_pid(char* pid)
{
	ssize_t ret = -2;
	int fd;
	int len = 0;
	fd = open(SERTEST, O_RDONLY);
	char buf[1];
	int index = 0;
	usleep(1000);
	if (fd == -1)
	{
		printf("Error with opening fd for %s in get_server_pid function\n", SERTEST);
		exit(EXIT_FAILURE); 
	}
	while (ret != 0)
	{
		ret = read(fd, buf, 1);
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

	freopen(SERTEST, "w", stdout);
	freopen(SERVOUT, "w", stdout);
	freopen("/dev/tty", "w", stdout);

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
		sstatus = check_server_output(argv[2]);
		kill_server(argv);
	}
	freopen("/dev/tty", "w", stdout);
	if(wstatus != 0 || sstatus != 0)
	{
		printf(RED "%d FAIL " RESET, testnum);
		freopen(SERClILOGS, "a+", stdout);
		printf("testnum: %d\n", testnum);
		printf("test case: %s\n", argv[2]);
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
	status += client_server_test(++testnum, (char *[]){"client", "", "a", NULL}, envp);
	status += client_server_test(++testnum, (char *[]){"client", "", "wooooow", NULL}, envp);
	status += client_server_test(++testnum, (char *[]){"client", "", "❤️❤️❤️❤️❤️❤️", NULL}, envp);
	status += client_server_test(++testnum, (char *[]){"client", "", "Tears welled in his distant acquaintance's eyes as he shared a gut-wrenching tale of his gravely ill daughter, depleted savings, and an unaffordable specialist. Desperation led to a plea for financial help. The man's compassion led him to write a check and seal their relationship with a sincere embrace. Days later, the truth emerged—no sick child, a deceitful scheme to hide gambling debts. Relief flooded him. 'Thank God—no little girl is dying!' he exclaimed. Amidst this revelation, amidst kindness and compassion, enlightenment dawned, bringing insight and joy.", NULL}, envp);
	status += client_server_test(++testnum, (char *[]){"client", "", "According to Tech Jury, despite a number of cool apps and tips for successful time management, only 17% of people track their time. 50% of people have never thought about time waste, even though they are always late and running out of time. Time management is a skill. It helps people handle their daily duties without burnout and severe exhaustion. The N.I.L.C. includes time management on the list of top ten demanded soft skills that employees require in 2022. Why is it so important to manage one’s time correctly? Stephen Covey once said, “The key is not spending time, but in investing it”. It means that proper timing guarantees a person’s success in many life areas. Career Trend names three negative aspects that occur when a person is not able to follow a schedule and be flexible. First off, one risks delaying the task performance all the time. People who got used to procrastination start doing assignments and duties at", NULL}, envp);
	printf("\n");
	if (status != 0)
		printf("There was something wrong, check %s\n", SERClILOGS);
}

