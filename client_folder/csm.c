/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   csm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:10:49 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/19 15:37:03 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	msg_status_start(pid_t pid)
{
	kill(pid, SIGUSR2);
	if (VERBOSE == 1)
		ft_putstr_fd("send sigusr2 msg status 1\n", STDOUT_FILENO);
	usleep(MSG_INTERVAL);
}

void	msg_status_end(pid_t pid, int msg_status)
{
	if (VERBOSE == 1)
	{
		ft_putstr_fd("msg status \n", STDOUT_FILENO);
		ft_putnbr_fd(msg_status, STDOUT_FILENO);
		ft_putstr_fd("(NULL)\n", STDOUT_FILENO);
	}
	sendbits('\0', pid);
	sleep(1);
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
		ft_putstr_fd("msg complete 6 \n", STDOUT_FILENO);
	return (7);
}
