/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:18:55 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 20:59:59 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	len_status_start(pid_t pid, int len_status, t_msg_c *g_msg)
{
	int	si;

	si = 0;
	while (g_msg->len_status != 2)
	{
		kill(pid, SIGUSR2);
		if (VERBOSE == 1)
		{
			ft_putstr_fd("send sigusr2 lenstatus: ", STDOUT_FILENO);
			ft_putnbr_fd(len_status, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		while (g_msg->len_status != 2 && si++ < 128000)
			usleep(1);
	}
}

void	len_status_sending(pid_t pid, t_msg_c *g_msg)
{
	int	si;

	si = 0;
	while (g_msg->len_status != 4)
	{
		kill(pid, SIGUSR1);
		while (g_msg->len_status != 4 && si++ < 100000)
			usleep(1);
	}
	if (VERBOSE == 1)
		ft_putstr_fd("send sigusr1 len\n", STDOUT_FILENO);
}

void	len_status_end(pid_t pid, int len_status, t_msg_c *g_msg)
{
	int	si;

	si = 0;
	while (g_msg->len_status != 6)
	{
		kill(pid, SIGUSR2);
		while (g_msg->len_status != 6 && si++ < 100000)
			usleep(1);
	}
	if (VERBOSE == 1)
	{
		ft_putstr_fd("send sigusr2 lenstatus: ", STDOUT_FILENO);
		ft_putnbr_fd(len_status, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	len_status_confirmation(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("len confirmation 2 \n", STDOUT_FILENO);
	return (2);
}

int	len_status_received(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("message received len \n", STDOUT_FILENO);
	return (4);
}
