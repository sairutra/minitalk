/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:45:32 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 21:00:26 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	msg_length_init(struct t_msg_s *msg, pid_t pid)
{
	msg->length += 1;
	if (VERBOSE == 1)
	{
		ft_putstr_fd("Len: ", STDOUT_FILENO);
		ft_putnbr_fd(msg->length, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	kill(pid, SIGUSR1);
}

void	len_status_confirm(struct t_msg_s *msg, pid_t pid)
{
	msg->len_status = 1;
	msg->length = 0;
	if (VERBOSE == 1)
	{
		ft_putstr_fd("len_status = 1 \n", STDOUT_FILENO);
		ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
	}
	kill(pid, SIGUSR2);
}

void	len_status_completion(struct t_msg_s *msg, pid_t pid)
{
	kill(pid, SIGUSR2);
	msg->len_status = 2;
	if (VERBOSE == 1)
	{
		ft_putstr_fd("len_status = 2 \n", STDOUT_FILENO);
		ft_putstr_fd("send sigusr 2 \n", STDOUT_FILENO);
	}
	msg->load = malloc(sizeof(char) * msg->length);
	if (msg->load == NULL)
		exit(EXIT_FAILURE);
}
