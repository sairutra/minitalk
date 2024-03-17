
#ifndef MINITALK_TESTER_H
# define MINITALK_TESTER_H

# define RED   "\x1B[31m"
# define GRN   "\x1B[1;32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define BMAG   "\x1B[1;35m"
# define CYN   "\x1B[36m"
# define BCYN   "\x1B[1;36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define CLIENTLOGS "logs/clientlogs.txt"
# define ClIOUTLOGS "logs/clientoutput.txt"
# define SEROUT "logs/server_start.txt"
# define SERLOGS "logs/serverlogs.txt"
# define SERTEST "testtemp/serverpid.txt"
# define SERVOUT "testtemp/serverout.txt"
# define SERClILOGS "logs/clientserverlogs.txt"
# define UNICODE_TEST "test_cases/unicode.txt"
# define OOOOOO1_TEST "test_cases/1.txt"
# define OOOOO10_TEST "test_cases/10.txt"
# define OOOO100_TEST "test_cases/100.txt"
# define OOO1000_TEST "test_cases/1000.txt"
# define OO10000_TEST "test_cases/10000.txt"

# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <bsd/string.h>
# include <fcntl.h>

void client_tests(char** envp);
void server_tests(char** envp);
void client_server_tests(char** envp);
#endif
