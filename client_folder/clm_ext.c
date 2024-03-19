/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clm_ext.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 15:21:23 by spenning      #+#    #+#                 */
/*   Updated: 2024/03/19 15:21:24 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	len_status_complete(void)
{
	if (VERBOSE == 1)
		ft_putstr_fd("len complete 6 \n", STDOUT_FILENO);
	return (6);
}
