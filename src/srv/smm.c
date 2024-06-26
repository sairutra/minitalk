/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   smm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:43:28 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 21:00:20 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	initialize_server_struct(struct t_msg_s *msg)
{
	if (VERBOSE == 1)
		ft_putstr_fd("server struct members initaliazed to 0\n", STDOUT_FILENO);
	msg->binaryindex = 0;
	msg->len_status = 0;
	msg->msg_status = 0;
	msg->index = 0;
	msg->length = 0;
	msg->load = NULL;
}

void	msg_status_confirm(struct t_msg_s *msg, pid_t pid)
{
	msg->msg_status = 1;
	if (VERBOSE == 1)
	{
		ft_putstr_fd("msg_status = 1 \n", STDOUT_FILENO);
		ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
	}
	kill(pid, SIGUSR2);
}

void	server_sigusr1(struct t_msg_s *msg, char *binary, pid_t pid)
{
	binary[msg->binaryindex] = 48;
	msg->binaryindex++;
	if (VERBOSE == 1)
		ft_putstr_fd("msg_status 1: sigusr1 (0)  \n", STDOUT_FILENO);
	if (VERBOSE == 1)
	{
		ft_putnbr_fd(msg->binaryindex, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	kill(pid, SIGUSR1);
}

void	server_sigusr2(struct t_msg_s *msg, char *binary, pid_t pid)
{
	binary[msg->binaryindex] = 49;
	msg->binaryindex++;
	if (VERBOSE == 1)
		ft_putstr_fd("msg_status 1: sigusr2 (1) \n", STDOUT_FILENO);
	if (VERBOSE == 1)
	{
		ft_putnbr_fd(msg->binaryindex, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	kill(pid, SIGUSR1);
}
