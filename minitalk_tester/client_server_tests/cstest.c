#include "../minitalk_tester.h"

enum { NS_PER_SECOND = 1000000000 };

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
	char buf[1000000];
	char *bufmalloc;
	char *buffin;
	char *temp;
	char *temp2;
	char *result;
	size_t lenbuf = 0;
	size_t lenmal = 0;
	usleep(100);
	bufmalloc = strdup("");
	if (bufmalloc == NULL)
	{
		printf("Error with bufmalloc in check_server_output function\n");
		exit(EXIT_FAILURE); 
	}
	fd1 = open(SERTEST, O_RDONLY);
	if (fd1 == -1)
	{
		printf("Error with opening fd for %s in check_server_output function\n", SERVOUT);
		exit(EXIT_FAILURE); 
	}
	while (ret != 0)
	{
		ret = read(fd1, buf, 10000);
		if(ret == -1)
		{
			printf("Error with reading in check_server_output function\n");
			exit(EXIT_FAILURE);
		}
		buf[ret] = '\0';
		lenbuf = strlen(buf);
		lenmal = strlen(bufmalloc);
		temp = bufmalloc;
		result = malloc(lenbuf+lenmal + 1);
		if (result == NULL)
		{
			printf("Error with bufmalloc + buf in check_server_output function\n");
			exit(EXIT_FAILURE); 
		}
		memcpy(result, bufmalloc, lenmal);
    	memcpy(result + lenmal, buf, lenbuf + 1);
		bufmalloc = result;
		free(temp);
	}
	while(bufmalloc[fnl] != '\n')
		fnl++;
	lnl = fnl + 1;
	while(bufmalloc[lnl] != '\n')
		lnl++;
	bufmalloc[lnl] = '\0';
	// printf("bufmalloc: %s\n", bufmalloc);
	temp2 = bufmalloc;
	buffin = malloc((strlen(bufmalloc)- fnl) + 1);
	if(buffin == NULL)
	{
			printf("Error with buffin in check_server_output function\n");
			exit(EXIT_FAILURE); 
	}
	strlcpy(buffin, bufmalloc + (fnl + 1), lnl - fnl);
	buffin[lnl-fnl] = '\0';
	// printf("buffin: %s\n", buffin);
	retint = strcmp(test, buffin); 
	if(retint)
	{
		freopen(SERClILOGS, "a+", stdout);
		
		printf("buf : %s\n", buffin); 
		// printf("bro wtf\n");
		printf("test: %s\n", test); 
		freopen("/dev/tty", "w", stdout);
	}
	free(temp2);
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

void sub_timespec(struct timespec t1, struct timespec t2, struct timespec *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
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
	struct tms before, after;
	double systime;
	double usrtime;
	clock_t resolution = sysconf(_SC_CLK_TCK);
	struct timespec start, finish, delta;
 
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
    clock_gettime(CLOCK_REALTIME, &start);
	times(&before); 
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
    	times(&after);
    	clock_gettime(CLOCK_REALTIME, &finish);
		kill_server(argv);
	}
	systime = (double)(after.tms_stime-before.tms_stime) / resolution;
	usrtime = (double)(after.tms_utime-before.tms_utime) / resolution;
    sub_timespec(start, finish, &delta);
	freopen("/dev/tty", "w", stdout);
	if(wstatus != 0 || sstatus != 0)
	{
		printf(BCYN "SYS TIME: %f\n" RESET, systime);
		printf(BCYN "USR TIME: %f\n" RESET, usrtime);
		printf(BCYN "REA TIME: %d.%.9ld\n" RESET, (int)delta.tv_sec, delta.tv_nsec);
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
		printf(BCYN "SYS TIME: %f\n" RESET, systime);
		printf(BCYN "USR TIME: %f\n" RESET, usrtime);
		printf(BCYN "REA TIME: %d.%.9ld\n" RESET, (int)delta.tv_sec, delta.tv_nsec);
		printf(GRN "%d OK " RESET, testnum);
		rstatus = 0;
	}
	return(rstatus);
}


char* readfile(char* path)
{
	ssize_t ret = -1;
	int fd;
	char buf[100000];
	char *testcase;
	size_t len = 0;

	fd = open(path, O_RDONLY);
	if(fd == -1)
	{
		printf("Open file in readfile function went wrong\n");
		exit(EXIT_FAILURE);
	}
	while(ret != 0)
	{
		ret = read(fd, buf, 100000);
		if(ret == -1)
		{
			printf("read in readfile function went wrong\n");
			exit(EXIT_FAILURE);
		}
		len += ret;
	}
	buf[len] = '\0';
	testcase = strdup(buf);
	if (testcase == NULL)
	{
		printf("strdup in readfile function went wrong\n");
		exit(EXIT_FAILURE);
	}
	return(testcase);
}


void client_server_tests(char** envp)
{
	int status = 0;
	int testnum = 0;
	char *testcase;

	printf(YEL "Client - Server\n" RESET);
	printf(BMAG "unicode\n" RESET);
	testcase = readfile(UNICODE_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf(BMAG "\nstring len: 1\n" RESET);
	testcase = readfile(OOOOOO1_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf(BMAG "\nstring len: 10\n" RESET);
	testcase = readfile(OOOOO10_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf(BMAG "\nstring len: 100\n" RESET);
	testcase = readfile(OOOO100_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf(BMAG "\nstring len: 1000\n" RESET);
	testcase = readfile(OOO1000_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf(BMAG "\nstring len: 10000\n" RESET);
	testcase = readfile(OO10000_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf(BMAG "\nstring len: 100000\n" RESET);
	testcase = readfile(O100000_TEST);
	status += client_server_test(++testnum, (char *[]){"client", "", testcase, NULL}, envp);
	free(testcase);
	printf("\n");
	if (status != 0)
		printf("There was something wrong, check %s\n", SERClILOGS);
}

