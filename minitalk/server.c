/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 21:37:29 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/01 16:24:21 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minitalk.h"

void	ft_putnumber(int number)
{
	long	n;

	n = number;
	if (number < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnumber(n / 10);
	n = n % 10 + 48;
	write(1, &n, 1);
}

// void	reset(char **string, int *strsize, int *intcount)
// {
// 	if (*string == NULL)
// 	{
// 		printf("zerou as condições");
// 		*intcount = 0;
// 		*strsize = 0;
// 	}
// }

void	wbits(int *intcount, unsigned char **string, int *strsize, int sig)
{
	static int	charcount;
	static int	index;

	if (charcount <= 7 && *intcount == 42)
	{
		if (*string)
			(*string)[index] = ((*string)[index]) | (sig << charcount);
		charcount++;
		if (charcount == 8)
		{
			index++;
			charcount = 0;
		}
	}
	if (index == *strsize)
	{
		(void)((*string) && (write(1, *string, *strsize + (*strsize == 0))));
		(void)((*string) && (write(1, "\n", 1)));
		printf("zerou as condições");
		*intcount = 0;
		charcount = 0;
		index = 0;
		*strsize = 0;
		(free(*string));
	}
}

void	handler(int sig)
{
	static unsigned char	*string;
	static int				strsize;
	static int				intcount;
	int						count;

	if (sig == SIGUSR1)
		sig = 1;
	else
		sig = 0;
	if (intcount < 32)
	{
		strsize = strsize | (sig << intcount++);
		return ;
	}
	if (intcount == 32)
	{
		string = malloc(strsize + 1 * sizeof(char));
		count = -1;
		while (++count <= strsize && (string))
			string[count] = '\0';
		intcount = 42;
	}
	wbits(&intcount, &string, &strsize, sig);
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "Pid: ", 5);
	ft_putnumber(pid);
	write(1, "\n", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
}
