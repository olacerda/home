/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root_messages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:25:32 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 10:58:32 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "terminal.h"

void	message_won(t_all *all)
{
	if (all->states->root == 1)
	{
		all->states->undefined_behavior = 0;
		all->states->ub_count = 0;
		all->states->full_colectables = 1;
		all->states->right_letters = 1;
		all->game->speed = 2;
		sheet_to_image(all->images->grass_wall_sheet, 
			all->images->background, NULL, 1);
		copy_map(all->map, all->map->map, "FIRAC");
		put_images(all, all->map, all->game->element, all->map->map);
		sheet_to_image(all->images->terminal_sheet, all->images->Y, 
			all->images->grass, 4);
		all->map->map[all->game->element[indexor("E")].line]
			[all->game->element[indexor("E")].column] = 'E';		
		mlx_put_image_to_window(all->mlx, all->window, all->images->Y->st,
			 all->game->element[indexor("Y")].px_column, 
			 	all->game->element[indexor("Y")].px_line);
	}
}

void	message_speed(t_all *all, int speed)
{
	if (all->states->root == 1)
	{
		if (speed > 5)
			speed = 5;
		if (speed == 0)
			speed = 1;
		all->game->usleep = (20000 / speed) - (200 * speed);
		all->states->root_speed = 1;
	}
}

void	message_able_desabe_ub_count(t_all *all, int *line, char (*writed)[33])
{
	if (cmp_msg(all, "desable ub count", writed[*line], 16) == 0)
	{
		if (all->states->ub_count == 1)
			all->states->ub_count_backup = 1;
		all->states->ub_count = 0;
		all->states->sound = 0;
	}
	else if (cmp_msg(all, "able ub count", writed[*line], 13) == 0)
	{
		all->states->ub_count_backup = 0;
		all->states->ub_count = 1;		
		all->states->sound = 1;
	}
}

void	message_able_desable_ub(t_all *all, int *line, char (*writed)[33])
{
	if (cmp_msg(all, "desable ub", writed[*line], 10) == 0)
	{
		all->states->undefined_behavior = 0;
		all->game->ub_current_time = all->game->ub_time + 1;
		all->images->background->img = all->images->grass->img;
		all->game->speed = 2;
		all->game->usleep = 20000;
		sheet_to_image(all->images->terminal_sheet, all->images->Y, 
			all->images->grass, 0);
		mlx_put_image_to_window(all->mlx, all->window, all->images->Y->st, 
			all->game->element[indexor("Y")].px_column, 
				all->game->element[indexor("Y")].px_line);
		rebuild_current_map(all);
	}
	if (cmp_msg(all, "able ub", writed[*line], 7) == 0)
	{
		if (all->states->won == 1)
			error_message(all, line, writed, 1);
		else
			all->states->undefined_behavior = 1;
	}
}