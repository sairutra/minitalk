/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:35:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/06 12:20:30 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

void sendBytesEnd(int pid)
{
	int index;

	index = 0;
	while (index <= 7)
	{
		kill(pid, SIGUSR2);
		index++;
		ft_printf("sigusr2: 1\n");
	}
}

void sendBits(unsigned char byte, int pid)
{
	int		index;
	
	index = 7;
	while (index >= 0)
	{
		if(byte & (1 << index))
		{
			kill(pid, SIGUSR2);
			write(1, "sigusr2: 1\n", 11);
			usleep(500);
		}
		else 
		{
			kill(pid, SIGUSR1);
			write(1, "sigusr1: 0\n", 11);
			usleep(500);
		}
		index--;
	}
}


int main (int argc, char **argv)
{
	int 	pid;
	int		index;
	char *	cstr;

	
	pid = ft_atoi(argv[1]);
	cstr = argv[2];
	index = 0;
	if (argc != 3)
	{
		ft_printf("%s", "Argument count is wrong: ./client pid string\n");
		exit(EXIT_FAILURE);
	}
	while(argv[2][index] != '\0')
	{
		printf("\n%c\n", argv[2][index]);
		sendBits(argv[2][index], pid);
		index++;
	}
	// sendBytesEnd(pid);
	return(0);
}
