/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:55:22 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/06 15:14:43 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

int binaryindex = 0;

int 	binaryToDecimal(char * binary)
{
	int index;
	int base;
	int dec_val;

	index = 7;
	base = 1;
	dec_val = 0;

	while (index >= 0)
	{
		if (binary[index] == '1')
			dec_val += base;
		base = base * 2;
		index--;
	}
	return(dec_val);
}


void handle_sigusr(int sig)
{
	int bit;
	static char binary[9];
	
	bit = 0;
	if(sig == SIGUSR1)
	{
		bit = 0;
		binary[binaryindex] = bit + 48;
		// write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
		// write(STDOUT_FILENO, "\n", 1);
		// write(1, "sigusr1: 0\n", 11);
		binaryindex++;
	}
	if(sig == SIGUSR2)
	{
		bit = 1;
		binary[binaryindex] = bit + 48;
		// write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
		// write(STDOUT_FILENO, "\n", 1);
		// write(1, "sigusr2: 1\n", 11);
		binaryindex++;
	}
	if(binaryindex == 8)
	{
		binary[8] = '\0';
		// write(STDOUT_FILENO, &binary, 8);
		// write(STDOUT_FILENO, "\n", 1);
		ft_putchar_fd(binaryToDecimal(binary), STDOUT_FILENO);
		// write(STDOUT_FILENO, "\n", 1);
		binaryindex = 0;
	}
}


int main ()
{	
	struct sigaction sa;
	sa.sa_handler = &handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%d\n", getpid());
	while (1)
	{
		sleep(1);
	}
	return(0);
}
