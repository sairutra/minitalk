#ifndef MINITALK_H
# define MINITALK_H


# include <unistd.h>
# include <stdio.h>
# include <signal.h>

typedef struct c_msg_t
{
	int start_length;
	int confirmation_length;
	int sending_length;
	int received_length;
	int complete_length;
	int complete_confirmation_length;
	int sending;
	int received;
	int pid;
	int printed;
}c_msg_t;

typedef struct s_msg_t
{
	int start_length;
	int complete_length;
	int length;
	int binaryindex;
	int received;
	int sending;
	int pid;
	char *load;
	int complete;
}s_msg_t;

#endif