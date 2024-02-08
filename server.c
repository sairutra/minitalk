/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mynodeus <mynodeus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:55:22 by spenning          #+#    #+#             */
/*   Updated: 2024/02/08 15:32:20 by mynodeus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

int binaryindex = 0;

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
		ft_putstr_fd("received pid:", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		write(1, "sigusr1: 0\n", 11);
		kill(info->si_pid, SIGUSR1);
		ft_putstr_fd("sending: ", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		binary[binaryindex] = 48;
		// write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
		// write(STDOUT_FILENO, "\n", 1);
		binaryindex++;
	}
	if(sig == SIGUSR2)
	{
		ft_putstr_fd("received: ", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		write(1, "sigusr2: 1\n", 11);
		kill(info->si_pid, SIGUSR1);
		ft_putstr_fd("sending: ", STDOUT_FILENO);
		ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		// ft_putnbr_fd(info->si_pid, STDOUT_FILENO);
		// write(STDOUT_FILENO, "\n", 1);
		binary[binaryindex] = 49;
		// write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
		// write(STDOUT_FILENO, "\n", 1);
		binaryindex++;
	}
	if(binaryindex == 8)
	{
		binary[8] = '\0';
		// write(STDOUT_FILENO, &binary, 8);
		// write(STDOUT_FILENO, "\n", 1);
		if(binaryToDecimal(binary) == 0)
			ft_putstr_fd("/0", STDOUT_FILENO);
		else
			ft_putchar_fd(binaryToDecimal(binary), STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		binaryindex = 0;
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
