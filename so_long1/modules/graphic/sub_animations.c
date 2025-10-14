/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_animations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:27 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:43:15 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "graphic.h"

void	update_memory_display(t_all *all)
{
	char memory;

	memory = "01234567898"[all->game->memory % 10];
	mlx_string_put(all->mlx, all->window, ((all->map->line_len - 2) * 64) 
		+ 25, 40, 0xFFFFFF, "Memory: ");
	mlx_string_put(all->mlx, all->window, (all->map->line_len - 1) * 64 + 10,
		 40, 0xFFFFFF, &memory);
}

char	*steps_to_string(t_all *all, int steps, int size2, int flag)
{
	static char str_steps[15];
	static int	index;
	int size;

	size = 0;
	if (flag > 0)
		index = 0;
	if (size2 > 0)
		size = size2;
	if (steps > 9)
		steps_to_string(all, steps / 10, size + 1, 0);
	if (steps <= 9)
		str_steps[size + 1] = '\0';
	str_steps[index++] = (steps % 10) + 48;
	if (size == 0)
		return (str_steps);
	return (NULL);
}

void	update_steps_display(t_all *all, int newcolumn, int newline)
{
	static int	column;
	static int	line;
	static int	steps;
	char 		*string;
	int			index;

	index = -1;
	mlx_string_put(all->mlx, all->window, ((all->map->line_len - 2) * 64) 
		+ 25, 20, 0xFFFFFF, "Steps: ");
	if (steps == 0 || (column != newcolumn) || (line != newline))
	{
		string = steps_to_string(all, steps, 0, 1);
		write(1, "Player steps:  ", 15);
		while (string[++index])
			write(1, &(string[index]), 1);
		write(1, "\n\n", 2);
		mlx_put_image_to_window(all->mlx, all->window, all->images->wall->st, 
			(all->map->line_len - 1) * 64, 0);
		mlx_string_put(all->mlx, all->window, ((all->map->line_len - 1) * 64) 
			+ 10, 20, 0xFFFFFF, string);
		string[0] = '\0';
		column = newcolumn;
		line = newline;
		steps++;
	}
}