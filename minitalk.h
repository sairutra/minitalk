#ifndef MINITALK_H
# define MINITALK_H


# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>

typedef struct c_msg_t
{
	pid_t	pid;
	int		len_status;
	int		msg_status;
}c_msg_t;

typedef struct s_msg_t
{
	int len_status;
	int msg_status;
	int binaryindex;
	int index;
	int length;
	char *load;
}s_msg_t;

#endif