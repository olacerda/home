/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_animations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:27 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 05:57:36 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

char	*steps_to_string(t_all *all, int steps, int size2, int flag)
{
	static char	str_steps[15];
	static int	index;
	int			size;

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

void	update_steps_display(t_all *all)
{
	char	*string;
	int		index;

	index = -1;
	string = steps_to_string(all, all->play->steps, 0, 1);
	write(1, "Player steps:  ", 15);
	while (string[++index])
		write(1, &(string[index]), 1);
	write(1, "\n\n", 2);
	mlx_string_put(all->mlx, all->window, ((all->map->line_len - 1) * 64)
		+ 10, 20, 0xFFFFFF, string);
	string[0] = '\0';
}

void	update_memory_display(t_all *all)
{
	char	memory[2];

	memory[0] = "01234567898"[all->game->memory % 10];
	memory [1] = '\0';
	mlx_string_put(all->mlx, all->window, (all->map->line_len - 1) * 64 + 10,
		40, 0xFFFFFF, memory);
}

void	update_step_and_memory(t_all *all, int flag)
{
	static int	steps = -1;
	static int	memory = -1;

	mlx_string_put(all->mlx, all->window, ((all->map->line_len - 2) * 64) + 25,
		20, 0xFFFFFF, "Steps: ");
	mlx_string_put(all->mlx, all->window, ((all->map->line_len - 2) * 64) + 25,
		40, 0xFFFFFF, "Memory: ");
	if (steps != all->play->steps || memory != all->game->memory
		|| steps == -1 || memory == -1 || flag)
	{
		mlx_put_image_to_window(all->mlx, all->window, all->images->wall->st,
			(all->map->line_len - 1) * 64, 0);
		update_steps_display(all);
		update_memory_display(all);
		steps = all->play->steps;
		memory = all->game->memory;
	}
}
