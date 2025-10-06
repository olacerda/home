/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matheus.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 23:59:06 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/06 00:01:46 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "so_long.h"

void	transparency(t_sheet *src, t_image *dst, t_image *background, int nbr)
{
	int	line;
	int index;
	int	column;

	line = -1;
	index = 0;
	while (++line < 64)
	{
		column = -1;
		while((++column < 64))
		{
			if (((int *)src->img)[index] == 16777215)
				((int *)dst->img)[index] = ((int *)background->img)[index];
			else
				((int *)dst->img)[index] = ((int *)src->img)[index];
			index++;		
		}
	}
}

int	main(void)
{
	
}