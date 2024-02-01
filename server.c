/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:55:22 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/01 18:59:53 by spenning      ########   odam.nl         */
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
	static char binary[8];
	
	bit = 0;
	if(binaryindex == 7)
	{
		binary[7] = '\0';
		write(STDOUT_FILENO, binary, 8);
		binaryindex = 0;
	}
	if(sig == SIGUSR1)
	{
		bit = 0;
		binary[binaryindex] = bit;
		binaryindex++;
		write(STDOUT_FILENO, "This is SIGUSR1\n", 16);
	}
	if(sig == SIGUSR2)
	{
		bit = 1;
		binary[binaryindex] = bit;
		binaryindex++;
		write(STDOUT_FILENO, "This is SIGUSR2\n", 16);
	}
	write(STDOUT_FILENO, ft_itoa(binaryindex), 1);
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
