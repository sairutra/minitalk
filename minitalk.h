#ifndef MINITALK_H
# define MINITALK_H


# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct c_msg_t
{
	int pid;
	int len_status;
	int msg_status;
}c_msg_t;

typedef struct s_msg_t
{
	int pid;
	int len_status;
	int msg_status;
	int binaryindex;
	int index;
	int length;
	char *load;
}s_msg_t;

#endif