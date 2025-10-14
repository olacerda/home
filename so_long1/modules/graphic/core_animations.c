/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_animations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:18 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:39:29 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "graphic.h"

void	player_animation(t_all *all)
{
	if (all->play->direction == 1)
	{
		if (all->game->usleep <= 5000 && all->play->movement == 1)
			update_bg(all->images->speed_player, all->images->background, 
				all, all->play->frame);
		else
			update_bg(all->images->player_sheet, all->images->background, 
				all, all->play->frame);
	}
	else
	{
		if (all->game->usleep <= 5000 && all->play->movement == 1)
			update_bg(all->images->speed_player_mirror, 
				all->images->background, all, all->play->frame);
		else
			update_bg(all->images->player_sheet_mirror, 
				all->images->background, all, all->play->frame);
	}
}

void	exit_animation(t_all *all)
{
	static int	column; 
	static int	line;
	static int	flag;

	if (flag == 0)
	{
		line = all->game->element[indexor("E")].px_line;
		column = all->game->element[indexor("E")].px_column;
		flag = 1;
	}
	if (all->states->won == 1)
	{
		sheet_to_image(all->images->exit_sheet, all->images->exit, 
			all->images->grass, all->game->exit_frame);
		mlx_put_image_to_window(all->mlx, all->window, all->images->exit->st,
			 column, line);
	}
}

void	update_animation_frames(t_all *all, float reference)
{
	static long 	time;
	static long 	last_exit;
	static long		last_player;

	reference = (60000 * (all->game->usleep / reference));
	time = get_full_time();
	if ((time - last_player > reference) || (last_player == 0))
	{
		if (all->play->movement == 1)
		{
			all->play->frame++;
			if (all->play->frame >= 16)
				all->play->frame = 0;
		}
		else
			all->play->frame = 13;
		last_player = time;
	}
	if ((time - last_exit > 60000) || (last_exit == 0))
	{
		all->game->exit_frame++;
		if (all->game->exit_frame >= 6)
			all->game->exit_frame = 0;
		last_exit = time;
	}
}