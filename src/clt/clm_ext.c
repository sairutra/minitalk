/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clm_ext.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mynodeus <mynodeus@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:21:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/06/23 20:59:50 by mynodeus      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	len_status_complete(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("len complete 6 \n", STDOUT_FILENO);
	return (6);
}
