/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:35:13 by spenning          #+#    #+#             */
/*   Updated: 2024/02/08 15:32:55 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

struct c_msg_t msg;

void sendBits(unsigned char byte, int pid)
{
	int		index;
	index = 7;
	while (index >= 0)
	{
		msg.sending = 1;
		msg.received = 0;
		ft_putstr_fd("sending", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		while (msg.sending == 1 && msg.received == 0)
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
			usleep(500);
			index--;
		}
	}
}

void sendBytesEnd(int pid)
{
	// int index;

	// index = 0;
	sendBits('\0', pid);
	// while (index <= 7)
	// {
	// 	kill(pid, SIGUSR2);
	// 	index++;
	// 	ft_printf("sigusr2: 1\n");
	// }
}

void handle_sigusr(int sig, siginfo_t* info, void *ucontext)
{
	if(msg.pid == info->si_pid)
	{
		if (sig == SIGUSR1)
		{
			msg.received = 1;
			msg.sending = 0;
			ft_putstr_fd("received pid: ", STDOUT_FILENO);
			ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		if (sig == SIGUSR2)
		{
			msg.sending = 0;
			msg.received = 1;
		}
	}
	else
	{
		ft_putstr_fd("wrong pid: ", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		ucontext_t *context = (ucontext_t*)ucontext;
  		unsigned long pc = context->uc_stack.ss_flags;
		ft_putnbr_fd(pc, STDOUT_FILENO);
	}
}


int main (int argc, char **argv)
{
	int 	pid;
	int		index;
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("%d\n", getpid());
	pid = ft_atoi(argv[1]);
	msg.pid = pid;
	msg.received = 1;
	index = 0;
	if (argc != 3)
	{
		ft_printf("%s", "Argument count is wrong: ./client pid string\n");
		exit(EXIT_FAILURE);
	}
	while(argv[2][index] != '\0')
	{
		printf("\n%c\n", argv[2][index]);
		sendBits(argv[2][index], pid);
		index++;
	}
	sendBytesEnd(pid);
	while (1)
	{
		sleep(1);
		if(msg.received == 0)
			ft_printf("ISNULL\n");
	}
	return(0);
}
