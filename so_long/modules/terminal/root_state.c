/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:16:30 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 02:34:45 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	message_su(t_all *all)
{
	static char	new_line_start[6];
	char		*to_copy;
	static int	size = 0;

	if (size == 0)
	{
		to_copy = "root%";
		size = -1;
		while (to_copy[++size])
			new_line_start[size] = to_copy[size];
		new_line_start[size] = '\0';
	}
	sheet_to_image(all->images->terminal_sheet, all->images->y,
		all->images->grass, 3);
	mlx_put_image_to_window(all->mlx, all->window, all->images->y->st,
		all->game->element[indexor("y")].px_column,
		all->game->element[indexor("y")].px_line);
	all->terminal->line_start = new_line_start;
	all->terminal->pc_nb_size = size + 1;
	all->states->root = 1;
}

void	message_exit(t_all *all)
{
	if (all->states->root == 1)
	{
		get_username_and_pcnumber(all, 1, 0);
		if (all->states->won == 0)
		{
			sheet_to_image(all->images->terminal_sheet, all->images->y,
				all->images->grass, 0);
			mlx_put_image_to_window(all->mlx, all->window, all->images->y->st,
				all->game->element[indexor("y")].px_column,
				all->game->element[indexor("y")].px_line);
		}
		if (all->states->ub_count_backup == 1)
		{
			all->states->ub_count = 1;
			all->states->ub_count_backup = 0;
		}
		all->game->speed = 2;
		all->states->root = 0;
		all->states->root_speed = 0;
		all->game->usleep = all->game->usleep_save - (((all->game->usleep_save
						- 5000) / all->game->element[indexor("C")].count)
				* all->play->colected);
	}
}
