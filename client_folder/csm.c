/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   csm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:10:49 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/21 14:05:37 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	msg_status_start(pid_t pid, c_msg_t *g_msg)
{
	int	si;

	si = 0;
	while (g_msg->msg_stat != 2)
	{
		kill(pid, SIGUSR2);
		while (g_msg->msg_stat != 2 && si++ < 100000)
			usleep(1);
	}
	if (VERBOSE == 1)
		ft_putstr_fd("send sigusr2 msg status 1\n", STDOUT_FILENO);
}

void	msg_status_end(pid_t pid, int msg_status, c_msg_t *g_msg)
{
	int	si;

	si = 0;
	while (g_msg->msg_stat != 7)
	{
		kill(pid, SIGUSR2);
		while (g_msg->msg_stat != 7 && si++ < 1000000)
			usleep(1);
	}
	if (VERBOSE == 1)
	{
		ft_putstr_fd("msg status \n", STDOUT_FILENO);
		ft_putnbr_fd(msg_status, STDOUT_FILENO);
		ft_putstr_fd("(NULL)\n", STDOUT_FILENO);
	}
}

int	msg_status_confirmation(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("msg confirmation 2 \n", STDOUT_FILENO);
	return (2);
}

int	msg_status_received(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("message received msg\n", STDOUT_FILENO);
	return (4);
}

int	msg_status_complete(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("msg complete 5 \n", STDOUT_FILENO);
	return (5);
}
