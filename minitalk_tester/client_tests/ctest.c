#include "../minitalk_tester.h"

int client_test(int testnum, char** argv, char** envp, int tstatus)
{
	pid_t pid;
	int estatus = 0;
	int wstatus = -1;
	int rstatus = -1;
	int errorindex = 0;
	int call = -1;

	freopen(ClIOUTLOGS, "a+", stdout);
	pid = fork();
	if(pid == 0)
	{
		estatus = execve("client", argv, envp);
		if(estatus == -1)
		{
			printf("Error with execve in client_tester function\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if(tstatus != 0)
			waitpid(pid, &wstatus, 0);
		else
		{
			call = kill(pid, 0);
			if(call == 0)
			{
				wstatus = 0;
				call = kill(pid, 9);
				if(call == -1)
				{
					printf("Error with kill child process in clien_test function\n");
				}
			}
		}
	}
	freopen("/dev/tty", "w", stdout);
	if(wstatus != tstatus)
	{
		printf(RED "%d FAIL " RESET, testnum);
		freopen(CLIENTLOGS, "a+", stdout);
		printf("testnum: %d\n", testnum);
		printf("expected process status (tstatus): %d\n", tstatus);
		printf("returned process status (wstatus): %d\n", wstatus);
		while(argv[errorindex] != NULL)
		{
			printf("argv[%d]: %s\n", errorindex, argv[errorindex]);
			errorindex++;
		}
		printf("-------------------------\n");
		freopen("/dev/tty", "w", stdout);
	}
	if(wstatus == tstatus)
	{
		printf(GRN "%d OK " RESET, testnum);
		rstatus = 0;
	}
	return(rstatus);
}

void client_tests(char** envp)
{
	int status = 0;
	int testnum = 0;
	printf(YEL "Client arguments\n" RESET);
	status += client_test(++testnum, (char *[]){"client", "2364845", "lol", NULL}, envp, 0);
	status += client_test(++testnum, (char *[]){"client", "2364845", "fjdsfkldsjfldsj", NULL}, envp, 0);
	status += client_test(++testnum, (char *[]){"client", "2364845", "ewcniewcinucnic2n3u23nu23nciu", NULL}, envp, 0);
	status += client_test(++testnum, (char *[]){"client", "2364845", "", NULL}, envp, 0);
	status += client_test(++testnum,(char *[]){"client", "2364854", "lol", "sike", NULL}, envp, 256);
	status += client_test(++testnum,(char *[]){"client", "2364854", "lol", "sike", "sike", NULL}, envp, 256);
	status += client_test(++testnum,(char *[]){"client", "2364854", "lol", "sike", "sike", "sike", NULL}, envp, 256);
	status += client_test(++testnum,(char *[]){"client", "2364854", "lol", "sike", "sike", "sike", "sike",NULL}, envp, 256);
	printf("\n");
	if (status != 0)
		printf("There was something wrong, check combination of %s and %s\n", CLIENTLOGS, ClIOUTLOGS);
}
