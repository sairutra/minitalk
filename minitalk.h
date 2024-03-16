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

# ifndef MSG_INTERVAL
#  define MSG_INTERVAL 50000
# endif

# ifndef SRV_INTERVAL
#  define SRV_INTERVAL 500
# endif

typedef struct c_msg_t
{
	volatile sig_atomic_t		pid;
	volatile sig_atomic_t		len_status;
	volatile sig_atomic_t		msg_status;
}c_msg_t;

typedef struct s_msg_t
{
	volatile sig_atomic_t len_status;
	volatile sig_atomic_t msg_status;
	volatile sig_atomic_t binaryindex;
	volatile sig_atomic_t index;
	volatile sig_atomic_t length;
	char *load;
}s_msg_t;

// client

void    len_status_start(pid_t pid, int len_status);
void    len_status_sending(pid_t pid);
void    len_status_end(pid_t pid, int len_status);
void    sendBits_SigUsr2(pid_t  pid);
void    sendBits_SigUsr1(pid_t  pid);
void    msg_status_start(pid_t pid);
void    SendLoad(char   load, pid_t   pid);
void 	sendBits(unsigned char byte, int pid);
void    msg_status_end(pid_t    pid, int    msg_status);
int     len_status_received(void);
int     len_status_confirmation(void);
int     len_status_complete(void);
int     msg_status_received(void);
int     msg_status_confirmation(void);
int     msg_status_complete(void);
void 	initialize_client_struct(struct c_msg_t *msg);

// server

void 	initialize_server_struct(struct s_msg_t *msg);
void    msg_length_init(struct s_msg_t *msg, pid_t pid);
void    len_status_confirm(struct s_msg_t *msg, pid_t pid);
void    len_status_completion(struct s_msg_t *msg, pid_t pid);
void    msg_status_confirm(struct s_msg_t *msg, pid_t pid);
void    server_sigusr1(struct s_msg_t *msg, char *binary, pid_t pid);
void    server_sigusr2(struct s_msg_t *msg, char *binary, pid_t pid);
void 	string_initializer(struct s_msg_t *msg, char *binary, pid_t pid);
void 	print_string(struct s_msg_t *msg, pid_t pid);
int 	binaryToDecimal(char * binary);
#endif