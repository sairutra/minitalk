/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:14:20 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 21:00:08 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	sendbits_sigusr2(pid_t pid)
{
	kill (pid, SIGUSR2);
	if (VERBOSE == 1)
		ft_putstr_fd("sigusr2: 1\n", STDOUT_FILENO);
}

void	sendbits_sigusr1(pid_t pid)
{
	kill (pid, SIGUSR1);
	if (VERBOSE == 1)
		ft_putstr_fd("sigusr1: 0\n", STDOUT_FILENO);
}

void	sendload(char load, pid_t pid)
{
	if (VERBOSE == 1)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putchar_fd(load, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	sendbits(load, pid);
}

void	initialize_client_struct(struct t_msg_c *msg)
{
	if (VERBOSE == 1)
		ft_putstr_fd("struct members initaliazed to 0\n", STDOUT_FILENO);
	msg->pid = 0;
	msg->msg_stat = 0;
	msg->len_status = 0;
}
