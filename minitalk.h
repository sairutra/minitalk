#ifndef MINITALK_H
# define MINITALK_H


# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct c_msg_t
{
	int received;
	int sending;
	int pid;
	char *load;
}c_msg_t;

#endif