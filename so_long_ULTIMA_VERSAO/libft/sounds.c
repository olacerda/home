/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:05:08 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/10 02:52:57 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <unistd.h>

void	teste(void)
{
	int	a = 3;
	
	while (a > 0)
	{
		write(1, "\a", 1);
		usleep(150000);
		write(1, "\a", 1);
		usleep(200000);
		write(1, "\a", 1);
		usleep(30000);
		write(1, "\a", 1);
		usleep(150000);
		write(1, "\a", 1);
		usleep(150000);
		write(1, "\a", 1);
		usleep(550000);
		a--;
	}
}

void alerta(void)
{
	int a = 10;
	int i;

	while (a > 0)
	{
		while (i < 6)
		{
			write(1, "\a", 1);
			usleep(100000);     // rápido
			i++;
		}
		i = 0;
		usleep(200000);         // pequena pausa
		while (i < 3)
		{
			write(1, "\a", 1);  
			usleep(150000);    // médio
			i++;
		}
		a--;		
	}
}

int	main(void)
{
	// teste();
	alerta();
}
