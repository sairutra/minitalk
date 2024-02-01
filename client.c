/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spenning <spenning@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 12:35:13 by spenning      #+#    #+#                 */
/*   Updated: 2024/02/01 15:59:09 by spenning      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "./libft/libft.h"

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


void printBits(unsigned char byte)
{
	int		index;
	int 	bit;
	
	bit = 0;
	index = 7;
	while (index >= 0)
	{
		if(byte & (1 << index))
			bit = 1;
		else 
			bit = 0;
		printf("%d", bit);
		index--;
	}
	printf("\n%c", binaryToDecimal("01100011"));
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
		printBits(argv[2][index]);
		index++;
	}
	return(0);
}
