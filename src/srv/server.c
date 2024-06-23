/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:55:22 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 21:00:33 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static struct t_msg_s	g_msg;

int	binarytodecimal(char *binary)
{
	int	index;
	int	base;
	int	dec_val;

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
	return (dec_val);
}

void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	static char	binary[9];

	(void)ucontext;
	if (sig == SIGUSR1)
	{
		if (g_msg.len_status == 1)
			msg_length_init(&g_msg, info->si_pid);
		if (g_msg.msg_status == 1)
			server_sigusr1(&g_msg, binary, info->si_pid);
	}
	if (sig == SIGUSR2)
	{
		if (g_msg.msg_status == 1)
			server_sigusr2(&g_msg, binary, info->si_pid);
		if (g_msg.len_status == 2 && g_msg.msg_status == 0)
			msg_status_confirm(&g_msg, info->si_pid);
		if (g_msg.len_status == 1)
			len_status_completion(&g_msg, info->si_pid);
		if (g_msg.len_status == 0)
			len_status_confirm(&g_msg, info->si_pid);
	}
	if (g_msg.binaryindex == 8)
		string_initializer(&g_msg, binary, info->si_pid);
}

int	main(void)
{
	struct sigaction	sa;
	int					ret;

	ret = 0;
	initialize_server_struct(&g_msg);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ret += sigaction(SIGUSR1, &sa, 0);
	ret += sigaction(SIGUSR2, &sa, 0);
	if (ret)
		exit(EXIT_FAILURE);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		sleep(1);
	return (0);
}
