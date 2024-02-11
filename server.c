/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:55:22 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/11 18:59:22 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

struct s_msg_t msg;

int 	binaryToDecimal(char * binary)
{
	int index;
	int base;
	int dec_val;

	index = 7;
	base = 1;
	dec_val = 0;

	while (index >= 0)
	{
		if (binary[index] == '1')
			dec_val += base;
		base = base * 2;
		index--;
	}
	return(dec_val);
}


void handle_sigusr(int sig, siginfo_t* info, void *ucontext)
{
	static char binary[9];
  	ucontext_t *context = (ucontext_t*)ucontext;
  	unsigned long pc = context->uc_stack.ss_flags;
	pc = pc -1;
	if(sig == SIGUSR1)
	{
		if(msg.start_length==1 && !msg.complete_length)
		{
			ft_putstr_fd("received pid1: ", STDOUT_FILENO);
			ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			msg.length += 1;
			ft_putnbr_fd(msg.length, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			kill(info->si_pid, SIGUSR1);	
		}
		usleep(500);
		// ft_putstr_fd("received pid:", STDOUT_FILENO);
		// ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		// write(1, "sigusr1: 0\n", 11);
		// kill(info->si_pid, SIGUSR1);
		// ft_putstr_fd("sending: ", STDOUT_FILENO);
		// ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		// ft_putchar_fd('\n', STDOUT_FILENO);
		// binary[binaryindex] = 48;
		// binaryindex++;
		// write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
		// write(STDOUT_FILENO, "\n", 1);
	}
	if(sig == SIGUSR2)
	{
		if(msg.start_length == 1 && !msg.complete_length)
		{
			msg.complete_length = 1;
			msg.load = malloc(sizeof(char) * msg.length);
			if (msg.load == NULL)
				exit(EXIT_FAILURE);
			msg.start_length = 0;
			kill(info->si_pid, SIGUSR2);
		}
		if(!msg.start_length)
		{
			msg.start_length = 1;
			msg.length = 0;
			kill(info->si_pid, SIGUSR2);	
		}	
		ft_putstr_fd("received2: ", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		write(1, "sigusr2: 1\n", 11);
		// kill(info->si_pid, SIGUSR1);
		ft_putstr_fd("sending: ", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		// ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		// write(STDOUT_FILENO, "\n", 1);
		binary[msg.binaryindex] = 49;
		// write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
		// write(STDOUT_FILENO, "\n", 1);
		usleep(500);
		msg.binaryindex++;
	}
	if(msg.binaryindex == 8)
	{
		binary[8] = '\0';
		// write(STDOUT_FILENO, &binary, 8);
		// write(STDOUT_FILENO, "\n", 1);
		if(binaryToDecimal(binary) == 0)
			ft_putstr_fd("/0", STDOUT_FILENO);
		else
			ft_putchar_fd(binaryToDecimal(binary), STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		msg.binaryindex = 0;
	}
}


int main ()
{	
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("%d\n", getpid());
	while (1)
	{
		sleep(1);
	}
	return(0);
}
