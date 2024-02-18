#ifndef MINITALK_H
# define MINITALK_H


# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
#include "./libft/libft.h"

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# ifndef LEN_INTERVAL
#  define LEN_INTERVAL 500000
# endif

# ifndef BIT_INTERVAL
#  define BIT_INTERVAL 10000
# endif

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

void    len_status_start(pid_t pid, int len_status);
void    len_status_sending(pid_t pid);
void    len_status_end(pid_t pid, int len_status);
void    sendBits_SigUsr2(pid_t  pid);
void    sendBits_SigUsr1(pid_t  pid);
#endif