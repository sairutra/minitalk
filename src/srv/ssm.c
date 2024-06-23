/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ssm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:42:19 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 21:00:14 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	print_string(struct t_msg_s *msg, pid_t pid)
{
	char	*temp;

	kill(pid, SIGUSR2);
	msg->load[msg->index] = '\0';
	ft_putendl_fd(msg->load, STDOUT_FILENO);
	temp = msg->load;
	free(temp);
	if (VERBOSE == 1)
		ft_putstr_fd("send complete sig2\n", STDOUT_FILENO);
	initialize_server_struct(msg);
	ft_putstr_fd("Server ready to receive string again\n", STDOUT_FILENO);
}

void	string_initializer(struct t_msg_s *msg, char *binary, pid_t pid)
{
	binary[8] = '\0';
	msg->binaryindex = 0;
	msg->load[msg->index] = binarytodecimal(binary);
	if (VERBOSE == 1)
	{
		ft_putstr_fd("msg load ", STDOUT_FILENO);
		ft_putchar_fd(msg->load[msg->index], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	msg->index += 1;
	if (msg->index == (msg->length - 1))
		print_string(msg, pid);
}
