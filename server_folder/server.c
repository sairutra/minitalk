/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:55:22 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/13 19:53:37 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

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
		if(msg.len_status==1)
		{
			msg.length += 1;
			ft_putstr_fd("Len: ", STDOUT_FILENO);
			ft_putnbr_fd(msg.length, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			kill(info->si_pid, SIGUSR1);	
		}
		if(msg.msg_status==1)
		{
			kill(info->si_pid, SIGUSR1);
			ft_putstr_fd("msg_status 1: sigusr1 (0)  \n", STDOUT_FILENO);
			binary[msg.binaryindex] = 48;
			msg.binaryindex++;
			ft_putnbr_fd(msg.binaryindex, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		usleep(SRV_INTERVAL);
	}
	if(sig == SIGUSR2)
	{
		if(msg.msg_status == 1)
		{
			kill(info->si_pid, SIGUSR1);
			ft_putstr_fd("msg_status 1: sigusr2 (1) \n", STDOUT_FILENO);
			binary[msg.binaryindex] = 49;
			msg.binaryindex++;
			ft_putnbr_fd(msg.binaryindex, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		if(msg.len_status == 2 && msg.msg_status == 0)
		{
			msg.msg_status = 1;
			ft_putstr_fd("msg_status = 1 \n", STDOUT_FILENO);
			ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
			kill(info->si_pid, SIGUSR2);
		}
		if(msg.len_status == 1)
		{
			kill(info->si_pid, SIGUSR2);
			msg.len_status = 2;
			ft_putstr_fd("len_status = 2 \n", STDOUT_FILENO);
			ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
			msg.load = malloc(sizeof(char) * msg.length);
			if (msg.load == NULL)
				exit(EXIT_FAILURE);
		}
		if(msg.len_status == 0)
		{
			msg.len_status = 1;
			ft_putstr_fd("len_status = 1 \n", STDOUT_FILENO);
			msg.length = 0;
			ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
			kill(info->si_pid, SIGUSR2);	
		}	
		usleep(SRV_INTERVAL);
	}
	if(msg.binaryindex == 8)
	{
		binary[8] = '\0';
		msg.binaryindex = 0;
		if(binaryToDecimal(binary) == 0)
		{
			msg.msg_status=2;
			ft_putstr_fd("send complete sig2\n", STDOUT_FILENO);
			usleep(SRV_INTERVAL);
			kill(info->si_pid, SIGUSR2);
			msg.load[msg.index] = '\0';
			write(STDOUT_FILENO, msg.load, (msg.length - 1));
			write(STDOUT_FILENO, "\n", 1);
			msg.binaryindex = 0;
		}
		else
		{
			msg.load[msg.index] = binaryToDecimal(binary);
			ft_putstr_fd("msg load ", STDOUT_FILENO);
			ft_putchar_fd(msg.load[msg.index], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			msg.index += 1;
		}
	}
}


int main ()
{	
	struct sigaction sa;

	initialize_server_struct(&msg);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("%d\n", getpid());
	while (1)
		sleep(1);
	return(0);
}
