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

#include "../minitalk.h"

struct c_msg_t msg;

void sendLength(const char * str, int pid)
{
	int length;

	length = ft_strlen(str);
	if(VERBOSE == 1)
	{
		ft_putnbr_fd(length, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	msg.len_status = 1;
	while(msg.len_status != 2)
		len_status_start(pid, msg.len_status);
	while(length >= 0)
	{
		msg.len_status = 3;
		while(msg.len_status != 4)
			len_status_sending(pid);
		length--;
	}
	msg.len_status = 5;
	while(msg.len_status != 6)
		len_status_end(pid, msg.len_status);
}

void sendBits(unsigned char byte, int pid)
{
	int		index;
	index = 7;
	while (index >= 0)
	{
		if(byte != '\0')
			msg.msg_status = 3;
		if(VERBOSE == 1)
			ft_putstr_fd("sending\n", STDOUT_FILENO);
		while (msg.msg_status != 4 && msg.msg_status != 6)
		{
			if(byte & (1 << index))
				sendBits_SigUsr2(pid);
			else 
				sendBits_SigUsr1(pid);
			usleep(BIT_INTERVAL);
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

	sendLength(load, pid);
	index = 0;
	msg.msg_status = 1;
	while(msg.msg_status != 2)
		msg_status_start(pid);
	while(load[index] != '\0')
		SendLoad(load[index++], pid);
	msg.msg_status = 5;
	while(msg.msg_status != 6)
		msg_status_end(pid, msg.msg_status);
}

int main (int argc, char **argv)
{
	struct 	sigaction sa;

	msg.len_status = 0;
	msg.msg_status = 0;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("%d\n", getpid());
	msg.pid = ft_atoi(argv[1]);
	if (argc != 3)
	{
		ft_printf("%s", "Argument count is wrong: ./client pid string\n");
		exit(EXIT_FAILURE);
	}
	sendmessage(argv[2], msg.pid);
	while (1)
		sleep(1);
	return(0);
}

