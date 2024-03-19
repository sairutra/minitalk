/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ssm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:42:19 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/19 16:19:45 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	print_string(struct s_msg_t *msg, pid_t pid)
{
	char	*temp;

	if (VERBOSE == 1)
		ft_putstr_fd("send complete sig2\n", STDOUT_FILENO);
	usleep(SRV_INTERVAL);
	msg->load[msg->index] = '\0';
	write(STDOUT_FILENO, msg->load, (msg->length - 1));
	write(STDOUT_FILENO, "\n", 1);
	temp = msg->load;
	free(temp);
	kill(pid, SIGUSR2);
	initialize_server_struct(msg);
	ft_putstr_fd("Server ready to receive string again\n", STDOUT_FILENO);
}

void	string_initializer(struct s_msg_t *msg, char *binary, pid_t pid)
{
	binary[8] = '\0';
	msg->binaryindex = 0;
	if (binarytodecimal(binary) == 0)
		print_string(msg, pid);
	else
	{
		msg->load[msg->index] = binarytodecimal(binary);
		if (VERBOSE == 1)
		{
			ft_putstr_fd("msg load ", STDOUT_FILENO);
			ft_putchar_fd(msg->load[msg->index], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		msg->index += 1;
	}
}
