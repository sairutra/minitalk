/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:35:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/21 14:04:47 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static struct c_msg_t	g_msg;

void	sendlength(const char *str, int pid)
{
	int	length;

	length = ft_strlen(str);
	if (VERBOSE == 1)
	{
		ft_putnbr_fd(length, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_msg.len_status = 1;
	len_status_start(pid, g_msg.len_status, &g_msg);
	while (length >= 0)
	{
		g_msg.len_status = 3;
		len_status_sending(pid, &g_msg);
		length--;
	}
	g_msg.len_status = 5;
	len_status_end(pid, g_msg.len_status, &g_msg);
}

void	sendbits(unsigned char byte, int pid)
{
	int		index;
	int		si;

	index = 7;
	si = 0;
	while (index >= 0)
	{
		g_msg.msg_stat = 3;
		while (g_msg.msg_stat != 4)
		{
			if (byte & (1 << index))
				sendbits_sigusr2(pid);
			else
				sendbits_sigusr1(pid);
			while (g_msg.msg_stat != 4 && si++ < 1000000)
				usleep(1);
		}
		index--;
	}
}

void	handle_sigusr(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGUSR1)
	{
		if (g_msg.len_status == 3)
			g_msg.len_status = len_status_received();
		if (g_msg.msg_stat == 3)
			g_msg.msg_stat = msg_status_received();
	}
	if (sig == SIGUSR2)
	{
		if (g_msg.len_status == 1)
			g_msg.len_status = len_status_confirmation();
		if (g_msg.len_status == 5)
			g_msg.len_status = len_status_complete();
		if (g_msg.msg_stat == 1)
			g_msg.msg_stat = msg_status_confirmation();
		if (g_msg.msg_stat == 4)
			g_msg.msg_stat = msg_status_complete();
	}
}

void	sendmessage(char *load, int pid)
{
	int		index;

	sendlength(load, pid);
	index = 0;
	g_msg.msg_stat = 1;
	msg_status_start(pid, &g_msg);
	while (load[index] != '\0')
		sendload(load[index++], pid);
	if (g_msg.msg_stat == 5)
		initialize_client_struct(&g_msg);
	ft_putstr_fd("Server ready for another message\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	initialize_client_struct(&g_msg);
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handle_sigusr;
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	ft_printf("%d\n", getpid());
	g_msg.pid = ft_atoi(argv[1]);
	if (argc != 3)
	{
		ft_printf("%s", "Argument count is wrong: ./client pid string\n");
		exit(EXIT_FAILURE);
	}
	sendmessage(argv[2], g_msg.pid);
	while (1)
		sleep(1);
	return (0);
}
