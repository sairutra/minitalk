#include "../minitalk_tester.h"

int check_file_empty()
{
	FILE *fp;
	fp = fopen(SEROUT, "r");
	if(fp == NULL)
	{
		printf("Error with file pointer in check_file_empty\n");
		exit(EXIT_FAILURE);
	}
	int c = fgetc(fp);
	if (c == EOF) 
	{
		ungetc(c, fp);
		fclose(fp);
		return(-1);
	} 
	else 
	{
		ungetc(c, fp);
		fclose(fp);
		return(0);
	}
}

int server_start_test(int testnum, char** argv, char** envp)
{
	pid_t pid;
	int estatus = -1;
	int rstatus = -1;
	int fstatus = -1;
	int call = -1;

	freopen(SEROUT, "a+", stdout);
	pid = fork();
	if(pid == 0)
	{
		estatus = execve("server", argv, envp);
		if(estatus == -1)
		{
			printf("Error with execve in server_start_test function\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		usleep(1000);
		call = kill(pid, 0);
		if(call == -1 && errno == ESRCH)
		{
			freopen("/dev/tty", "w", stdout);
			printf(RED "%d FAIL " RESET, testnum);
			freopen(SEROUT, "a+", stdout);
			printf("testnum: %d\n", testnum);
			printf("PID is not existent of server\n");
			printf("server is still active so server process should be terminated\n");
			printf("-------------------------\n");
			testnum++;
		}
		if(call == 0)
		{
			call = kill(pid, 9);
			if(call == -1 && errno == ESRCH)
			{
				printf("Error with kill child process in server_start_test function\n");
				exit(EXIT_FAILURE);
			}
			freopen("/dev/tty", "w", stdout);
			printf(GRN "%d OK " RESET, testnum);
			testnum++;
		}
	}
	freopen("/dev/tty", "w", stdout);
	fstatus = check_file_empty();
	if(fstatus != 0)
	{
		printf(RED "%d FAIL " RESET, testnum);
		freopen(SERLOGS, "a+", stdout);
		printf("testnum: %d\n", testnum);
		printf("File is empty, server does not print pid\n");
		printf("-------------------------\n");
		freopen("/dev/tty", "w", stdout);
	}
	if(fstatus == 0)
	{
		printf(GRN "%d OK " RESET, testnum);
		rstatus = 0;
	}
	return(rstatus);
}

void server_tests(char** envp)
{
	int status = 0;
	int testnum = 0;
	printf(YEL "Server\n" RESET);
	status += server_start_test(++testnum, (char *[]){"server", "",NULL}, envp);
	printf("\n");
	if (status != 0)
		printf("There was something wrong, check combination %s and %s\n", SERLOGS, SEROUT);
}

