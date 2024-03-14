/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:55:22 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/14 11:22:03 by spenning      ########   odam.nl         */
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
	(void)ucontext;
	if(sig == SIGUSR1)
	{
		if(msg.len_status==1)
			msg_length_init(&msg, info->si_pid);
		if(msg.msg_status==1)
			server_sigusr1(&msg, binary, info->si_pid);
		usleep(SRV_INTERVAL);
	}
	if(sig == SIGUSR2)
	{
		if(msg.msg_status == 1)
			server_sigusr2(&msg, binary, info->si_pid);
		if(msg.len_status == 2 && msg.msg_status == 0)
			msg_status_confirm(&msg, info->si_pid);
		if(msg.len_status == 1)
			len_status_completion(&msg, info->si_pid);
		if(msg.len_status == 0)
			len_status_confirm(&msg, info->si_pid);
		usleep(SRV_INTERVAL);
	}
	if(msg.binaryindex == 8)
		string_initializer(&msg, binary, info->si_pid);
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
