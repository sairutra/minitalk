#include "minitalk_tester.h"

void create_directory(char * name, char * functionname, char * program)
{
	int result = 0;
	DIR* dir = opendir(name);
	if (dir) {
		closedir(dir);
	} else if (ENOENT == errno) {
		result = mkdir(name, 0777);
		if (result == -1)
		{
			printf("Error with creating %s directory in %s of %s\n", name, functionname, program);
			exit(EXIT_FAILURE);	
		}
	} else {
		printf("Error with checking for %s directory in %s of %s\n", name, functionname, program);
		exit(EXIT_FAILURE);
	}
}

int main (int argc, char **argv, char **envp)
{
	create_directory("logs", "main", "minitalk_tester");
	freopen(CLIENTLOGS, "w", stdout);
	freopen(ClIOUTLOGS, "w", stdout);
	freopen("/dev/tty", "w", stdout);
	(void)argv;
	(void)argc;
	client_tests(envp);
	return(0);
}
