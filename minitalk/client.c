/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:53:38 by otlacerd          #+#    #+#             */
/*   Updated: 2025/08/28 16:28:07 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minitalk.h"
// else
// 	bitworker((unsigned int)ft_atoi(argv[1]), ft_stringjoin(argc, argv));
// int	joinsize(int size, char **string)
// {
// 	int	result;
// 	int	big;
// 	int	small;

// 	big = 1;
// 	result = 0;
// 	while (big < size)
// 	{
// 		small = -1;
// 		while (string[big][++small] != '\0')
// 			result++;
// 		big++;
// 	}
// 	return (result);
// }

// char	*ft_stringjoin(int size, char **string)
// {
// 	char	*result;
// 	int		resultsize;
// 	int		resultindex;
// 	int		big;
// 	int		small;

// 	resultsize = joinsize(size, string);
// 	resultindex = 0;
// 	result = malloc((resultsize + ((size - 2) * 3) + 1) * sizeof(char));
// 	if (!result || size < 3)
// 		return (NULL);
// 	big = 2;
// 	while (big < size)
// 	{
// 		small = -1;
// 		result[resultindex++] = '"';
// 		while (string[big][++small] != '\0')
// 			result[resultindex++] = string[big][small];
// 		result[resultindex++] = '"';
// 		if (++big < size)
// 			result[resultindex++] = ' ';
// 	}
// 	result[resultindex] = '\0';
// 	return (result);
// }

void	myhandler(int nbr)
{
	if (nbr == 12)
	{
		write(1, "Good choice.\n *Process finished**\n", 34);
		exit(1);
	}
	if (nbr == 10)
		return ;
	else if (nbr > 0)
		myhandler(nbr / 10);
	write(1, &"0123456789"[nbr % 10], 1);	
}

int	ft_atoi(char *string)
{
	int	result;
	int	index;
	int	minus;

	minus = 0;
	result = 0;
	index = 0;
	if (string == NULL)
		return (0);
	if (string[index] == '-')
	{
		minus = 1;
		index++;
	}
	index -= 1;
	while (string[++index] != '\0')
		result = result * 10 + (string[index] - 48);
	if (minus > 0)
		result = -result;
	return (result);
}

void	sbits(char *string, int size, int pid, int killcheck)
{
	int		index;
	char	charcount;

	index = 0;
	if (size == 0)
		kill(pid, SIGUSR2);
	else
	{
		while (string[index] != '\0')
		{
			charcount = 0;
			while (charcount < 8)
			{
				if (((string[index]) >> charcount) & 1)
					kill(pid, SIGUSR1);
				else
					kill(pid, SIGUSR2);
				if (killcheck < 0)
					exit (1);
				charcount++;
				usleep(350);
			}
			index++;
		}		
	}
}

void	bitworker(int pid, char *string)
{
	int	intcount;
	int	size;
	int	killcheck;

	intcount = 0;
	size = 0;
	killcheck = 0;
	if (string == NULL)
		return ;
	while (string[size])
		size++;
	while (intcount < 32)
	{
		if ((size >> intcount) & 1)
			killcheck = kill(pid, SIGUSR1);
		else
			killcheck = kill(pid, SIGUSR2);
		if (killcheck < 0)
			exit(1);
		intcount++;
		usleep(350);
	}
	sbits(string, size, pid, killcheck);
}

int	main(int argc, char *argv[])
{
	int		mypid;

	signal(SIGUSR1, myhandler);
	signal(SIGUSR2, myhandler);
	mypid = getpid();
	if (argc != 3)
		write(2, "\nWrong amount of arguments!!!\n\n", 31);
	else
	{
		if (ft_atoi(argv[1]) <= 0)
		{
			write(2, "\nDangerous PID for this project!\n\nContinue?...", 45);
			write(2, "\n1.(Yes) Type: \"kill -10 ", 26);
			myhandler(mypid);
			write(2, "\" in other terminal. \n2.(No)  Type: \"kill -12 ", 46);
			myhandler(mypid);
			write(2, "\" in other terminal. (or Ctrl + C)\n", 35);
			pause();
		}
		if (ft_atoi(argv[1]) <= 0)
		{
			write(2, "\n!!Please be more careful with the evaluation!!!\n", 43);
			return (1);
		}
		if (argc == 3)
			bitworker((unsigned int)ft_atoi(argv[1]), argv[2]);
	}
	return (1);
}
