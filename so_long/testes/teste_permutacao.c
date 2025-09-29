/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_permutacao.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 22:24:46 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/25 23:17:35 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	permutacao(int a, int b, int c, int d)
{
	int	count = 0;
	while (a < 5)
	{
		b = 1;
		while (b < 5)
		{
			if (b != a)
			{
				c = 1;
				while (c < 5)
				{
					if (c != a && c != b)
					{
						d = 1;
						while (d < 5)
						{
							if (d != a && d != b && d != c)
							{
								count ++;
								printf("%d %d %d %d    count: %d\n", a, b, c, d, count);
							}
							d++;
						}
					}
					c++;
				}
			}	
			b++;
		}
		a++;
	}
}



int	main(void)
{
	int a = 1;
	int b = 1;
	int c = 1;
	int d = 1;

	permutacao(a, b, c, d);
}