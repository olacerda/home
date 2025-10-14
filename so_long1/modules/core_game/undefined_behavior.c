/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undefined_behavior.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:14:17 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:52:07 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core_game.h"

void	display_indefined_behavior_alert(t_all *all)
{
	static int	changer = 1;
	if (all->states->ub_count == 1)
	{
		if (changer == 2)
		{
			sheet_to_image(all->images->terminal_sheet, all->images->Y, 
				all->images->grass, 1);
			changer = 1;
		}
		else
		{
			sheet_to_image(all->images->terminal_sheet, all->images->Y, 
				all->images->grass, 2);
			changer = 2;
		}
		mlx_put_image_to_window(all->mlx, all->window, all->images->Y->st, 
			all->game->element[indexor("Y")].px_column, 
				all->game->element[indexor("Y")].px_line);
	}
	mlx_do_sync(all->mlx);
}

void	display_ub_count(t_all_images *images, int ub_time, t_all *all)
{
	int	center;

	center = ((all->map->line_len * WIDE) / 2);
	if (ub_time > 9)
		sheet_to_image(images->let_sheet, images->nbr1, images->wall, 
			(ub_time / 10) - 1);
	else
		sheet_to_image(images->grass_wall_sheet, images->nbr1, NULL, 0);
	mlx_put_image_to_window(all->mlx, all->window, images->nbr1->st, center
		- WIDE, 0 * TALL);
	mlx_do_sync(all->mlx);
	if (ub_time <= 5)
	{
		if (ub_time >= 0)
			sheet_to_image(images->red_let_sheet, images->nbr2, images->wall, 
				((ub_time % 10) - 1) + (10 * (((ub_time % 10)) == 0)));
		sheet_to_image(images->red_let_sheet, images->nbr1, images->wall, 39);
		mlx_put_image_to_window(all->mlx, all->window, images->nbr1->st, center 
			+ WIDE, 0 * TALL);
	}
	else
		sheet_to_image(images->let_sheet, images->nbr2, images->wall, 
			((ub_time % 10) - 1) + (10 * (((ub_time % 10)) == 0)));
	mlx_put_image_to_window(all->mlx, all->window, images->nbr2->st, 
		center, 0 * TALL);
}

void	redefine_behavior_directions(t_all *all, long *time, long *last)
{
		static int flag = 0;

		if (*time - *last > 2600000)
			subvert_behavior(all, &flag);
		if (*time - *last > 3500000 && flag == 1)
		{
			(all->game->speed2) = -(all->game->speed2);
			flag = 2;
		}
		if (*time - *last > 5500000)
		{
			(all->game->speed2) = -(all->game->speed2);
			(all->game->speed) = -(all->game->speed);
			*last = *time;
			flag = 0;
		}
}

void	redefine_behavior(t_all *all)
{
		static long time = 0;
		static long last = 0;

		time = get_full_time();
		if (all->game->speed == 2)
		{
			if (all->play->letter_colected[all->play->lttrs_cnt - 1])
				all->images->background->img = 
				all->game->element[indexor(&(all->play->letter_colected[all->
					play->lttrs_cnt - 1]))].img;
			all->game->usleep = 65000;
			(all->game->speed) = 16;
			last = time;
		}
		if (time - last > 2000000)
		{
			all->game->usleep = 20000;
			(all->game->speed < 0) && (all->game->speed = -40);
			(all->game->speed > 0) && (all->game->speed = 40);
			all->images->background->img = all->images->player->img;
		}
		redefine_behavior_directions(all, &time, &last);
}

void	ub_count(t_all *all)
{
	static long time;
	static long last;

	time = get_full_time();
	if (all->game->ub_current_time > all->game->ub_time)
	{
		all->game->ub_current_time = all->game->ub_time;
		last = time;
		display_ub_count(all->images, all->game->ub_current_time, all);
		display_indefined_behavior_alert(all);
	}
	if (time - last > 500000)
		display_indefined_behavior_alert(all);
	if (time - last > 1000000)
	{
		(void)((all->states->ub_count == 1) && (all->game->ub_current_time)--);
		display_ub_count(all->images, all->game->ub_current_time, all);
		display_indefined_behavior_alert(all);
		if (all->game->ub_current_time <= 0)
		{
			usleep(200000);
			end_game(all);
		}
		last = time;
	}
}