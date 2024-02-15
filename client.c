/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:35:13 by spenning          #+#    #+#             */
/*   Updated: 2024/02/15 11:54:26 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

struct c_msg_t msg;

void sendLength(const char * str, int pid)
{
	int length;

	length = ft_strlen(str);
	ft_putnbr_fd(length, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	msg.len_status = 1;
	while(msg.len_status != 2)
	{
		kill(pid, SIGUSR2);
		ft_putstr_fd("send sigusr2 lenstatus: ", STDOUT_FILENO);
		ft_putnbr_fd(msg.len_status, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		usleep(500000);
	}
	while(length >= 0)
	{
		msg.len_status = 3;
		while(msg.len_status != 4)
		{
			ft_putstr_fd("send sigusr1 len\n", STDOUT_FILENO);
			kill(pid, SIGUSR1);
			usleep(50000);
		}
		length--;
	}
	msg.len_status = 5;
	while(msg.len_status != 6)
	{
		kill(pid, SIGUSR2);
		ft_putstr_fd("send sigusr2 lenstatus: ", STDOUT_FILENO);
		ft_putnbr_fd(msg.len_status, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		usleep(150000);
	}
}

void sendBits(unsigned char byte, int pid)
{
	int		index;
	index = 7;
	while (index >= 0)
	{
		if(byte != '\0')
			msg.msg_status = 3;
		ft_putstr_fd("sending\n", STDOUT_FILENO);
		while (msg.msg_status != 4 && msg.msg_status != 6)
		{
			if(byte & (1 << index))
			{
				kill(pid, SIGUSR2);
				write(1, "sigusr2: 1\n", 11);
			}
			else 
			{
				kill(pid, SIGUSR1);
				write(1, "sigusr1: 0\n", 11);
			}
			usleep(10000);
			index--;
		}
	}
}

void handle_sigusr(int sig, siginfo_t* info, void *ucontext)
{
	ucontext_t *context = (ucontext_t*)ucontext;
  	unsigned long pc = context->uc_stack.ss_flags;
	pc = pc -1;
	int pid = info->si_pid;
	pid = pid -1;
	if (sig == SIGUSR1)
	{
		if(msg.len_status == 3)
		{
			ft_putstr_fd("message received len \n", STDOUT_FILENO);
			msg.len_status = 4;
		}
		if(msg.msg_status == 3)
		{
			ft_putstr_fd("message received msg\n", STDOUT_FILENO);
			msg.msg_status = 4;
		}
	}
	if (sig == SIGUSR2)
	{
		if(msg.len_status == 1)
		{
			ft_putstr_fd("len confirmation 2 \n", STDOUT_FILENO);
			msg.len_status = 2;
		}
		if(msg.len_status == 5)
		{	
			ft_putstr_fd("len complete 6 \n", STDOUT_FILENO);
			msg.len_status = 6;
		}
		if(msg.msg_status == 1)
		{
			ft_putstr_fd("msg confirmation 2 \n", STDOUT_FILENO);
			msg.msg_status = 2;
		}
		ft_putstr_fd("lol \n", STDOUT_FILENO);
		if(msg.msg_status == 5)
		{	
			ft_putstr_fd("msg complete 6 \n", STDOUT_FILENO);
			msg.msg_status = 6;
		}
		
	}
}


void sendmessage(char *load, int pid)
{
	int		index;

	index = 0;
	sendLength(load, pid);
	msg.msg_status = 1;
	while(msg.msg_status != 2)
	{
		kill(pid, SIGUSR2);
		ft_putstr_fd("send sigusr2 msg status 1\n", STDOUT_FILENO);
		usleep(50000);
	}
	while(load[index] != '\0')
	{
		printf("\n%c\n", load[index]);
		sendBits(load[index], pid);
		usleep(50000);
		index++;
	}
	msg.msg_status = 5;
	while(msg.msg_status != 6)
	{
		ft_putstr_fd("msg status \n", STDOUT_FILENO);
		ft_putnbr_fd(msg.msg_status, STDOUT_FILENO);
		ft_putstr_fd("(NULL)\n", STDOUT_FILENO);
		sendBits('\0', pid);
		sleep(1);
	}
}

int main (int argc, char **argv)
{
	int 	pid;
	struct sigaction sa;

	msg.len_status = 0;
	msg.msg_status = 0;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("%d\n", getpid());
	pid = ft_atoi(argv[1]);
	msg.pid = pid;
	if (argc != 3)
	{
		ft_printf("%s", "Argument count is wrong: ./client pid string\n");
		exit(EXIT_FAILURE);
	}
	sendmessage(argv[2], pid);
	while (1)
		sleep(1);
	return(0);
}

