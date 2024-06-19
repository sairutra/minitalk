/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/21 14:10:29 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/19 21:01:28 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>
# include "./libft/inc/libft.h"

# ifndef VERBOSE
#  define VERBOSE 0
# endif

typedef struct t_msg_c
{
	volatile sig_atomic_t	pid;
	volatile sig_atomic_t	len_status;
	volatile sig_atomic_t	msg_stat;
}	t_msg_c;

typedef struct t_msg_s
{
	volatile sig_atomic_t	len_status;
	volatile sig_atomic_t	msg_status;
	volatile sig_atomic_t	binaryindex;
	volatile sig_atomic_t	index;
	volatile sig_atomic_t	length;
	char					*load;
}	t_msg_s;

// client

void	len_status_start(pid_t pid, int len_status, struct t_msg_c *msg);
void	len_status_sending(pid_t pid, struct t_msg_c *msg);
void	len_status_end(pid_t pid, int len_status, struct t_msg_c *msg);
void	sendbits_sigusr2(pid_t pid);
void	sendbits_sigusr1(pid_t pid);
void	msg_status_start(pid_t pid, struct t_msg_c *msg);
void	sendload(char load, pid_t pid);
void	sendbits(unsigned char byte, int pid);
void	msg_status_end(pid_t pid, int msg_status, struct t_msg_c *msg);
int		len_status_received(void);
int		len_status_confirmation(void);
int		len_status_complete(void);
int		msg_status_received(void);
int		msg_status_confirmation(void);
int		msg_status_complete(void);
void	initialize_client_struct(struct t_msg_c *msg);

// server

void	initialize_server_struct(struct t_msg_s *msg);
void	msg_length_init(struct t_msg_s *msg, pid_t pid);
void	len_status_confirm(struct t_msg_s *msg, pid_t pid);
void	len_status_completion(struct t_msg_s *msg, pid_t pid);
void	msg_status_confirm(struct t_msg_s *msg, pid_t pid);
void	server_sigusr1(struct t_msg_s *msg, char *binary, pid_t pid);
void	server_sigusr2(struct t_msg_s *msg, char *binary, pid_t pid);
void	string_initializer(struct t_msg_s *msg, char *binary, pid_t pid);
void	print_string(struct t_msg_s *msg, pid_t pid);
int		binarytodecimal(char *binary);
#endif