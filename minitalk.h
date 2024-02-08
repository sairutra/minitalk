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
	int printed;
}c_msg_t;

typedef struct s_msg_t
{
	int received;
	int sending;
	int pid;
	char *load;
	int complete;
}s_msg_t;

#endif