/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:35:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/11 18:32:38 by spenning      ########   odam.nl         */
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
	msg.start_length = 1;
	while(!msg.confirmation_length)
	{
		kill(pid, SIGUSR2);
		usleep(5000);
	}
	while(length >= 0)
	{
		msg.sending_length = 1;
		msg.received_length = 0;
		while(msg.received_length != 1)
		{
			ft_putstr_fd("send sigusr1 len", STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			kill(pid, SIGUSR1);
			usleep(5000);
		}
		length--;
	}
	msg.start_length = 0;
	msg.confirmation_length = 0;
	msg.sending_length = 0;
	msg.received_length= 0;
	msg.complete_length = 1;
	while(!msg.complete_confirmation_length)
	{
		kill(pid, SIGUSR2);
		usleep(5000);
	}
}

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

void handle_sigusr(int sig, siginfo_t* info, void *ucontext)
{
	if(msg.pid == info->si_pid)
	{
		if (sig == SIGUSR1)
		{
			if(msg.start_length == 1 && msg.confirmation_length == 1 && msg.sending_length == 1)
			{
				msg.received_length = 1;
				msg.sending_length = 0;
			}
			else{
			msg.received = 1;
			msg.sending = 0;
			ft_putstr_fd("received pid1: ", STDOUT_FILENO);
			ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			}
		}
		if (sig == SIGUSR2)
		{
			if(msg.start_length == 1 && !msg.confirmation_length)
			{
				ft_putstr_fd("confirmation_length = 1 \n", STDOUT_FILENO);
				msg.confirmation_length = 1;
			}
			if(msg.complete_length == 1 && !msg.complete_confirmation_length)
			{	
				ft_putstr_fd("complete_confirmation_length = 1 \n", STDOUT_FILENO);
				msg.complete_confirmation_length = 1;
			}
			else{
			msg.sending = 0;
			msg.received = 1;
			}
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
	sendLength(argv[2], pid);
	// while(argv[2][index] != '\0')
	// {
	// 	printf("\n%c\n", argv[2][index]);
	// 	sendBits(argv[2][index], pid);
	// 	index++;
	// }
	// sendBits('\0', pid);
	while (1)
	{
		sleep(1);
		// if(msg.received == 0)
		// 	ft_printf("ISNULL\n");
	}
	return(0);
}
