/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:59 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:48:47 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core_game.h"

void	update_game(t_all *all)
{
	if ((all->states->full_colectables == 0) && (check_hitbox(all, 'C') == 1))
	{
		if (++all->play->colected >= all->game->element[indexor("C")].count)
			all->states->full_colectables = 1;
		if (all->states->root_speed == 0)
		{
			all->game->usleep = all->game->usleep_save - (((all->game->
				usleep_save - 5000) / all->game->element[indexor("C")].count)
					 * all->play->colected);
		}
	}
	else if  ((all->play->F == 0) && (check_hitbox(all, 'F') == 1))
		all->play->F = 1;
	else if ((all->play->I == 0) && (check_hitbox(all, 'I') == 1))
		all->play->I = 1;
	else if ((all->play->R == 0) && (check_hitbox(all, 'R') == 1))
		all->play->R = 1;
	else if ((all->play->A == 0) && (check_hitbox(all, 'A') == 1))
		all->play->A = 1;
	update_major_elements(all, all->game->element[indexor("E")].line, 
		all->game->element[indexor("E")].column);
	update_steps_display(all, (all->game->element[indexor("P")].px_column + 31)
		/ 64, (all->game->element[indexor("P")].px_line + 31) / 64);
	if (all->states->bonus == 1)
		update_memory_display(all);
}

void update_major_elements(t_all *all, int line, int column)
{
	void	*exit_mlx;

	exit_mlx = all->images->exit->st;
	if (all->states->full_colectables == 1 && all->states->won == 0 && 
		((all->states->right_letters == 1) || (all->states->bonus == 0)))
	{
		all->states->won = 1;
		all->map->map[line][column] = 'E';
		mlx_put_image_to_window(all->mlx, all->window, exit_mlx, column * 64, 
			line * 64);
	}
	if ((check_hitbox(all, 'E') == 1) && (all->states->won == 1) && 
		(all->states->undefined_behavior == 0))
	{
		all->states->full_colectables = 0;
		end_game(all);
	}
}

void	check_letters_colected(t_all *all, char	element, int line, int column)
{
	int			index;
	char *letters;

	letters = "FIRA";
	index = -1;
	if (element == 'F' || element == 'I' || element == 'R' || element == 'A')
	{
		all->play->letter_colected[all->play->lttrs_cnt] = 
			all->map->map[line][column];
		all->play->lttrs_cnt++;
		if (all->states->undefined_behavior == 1 && all->states->ub_count == 1)
		{
			all->game->ub_current_time -= 5;
			display_ub_count(all->images, all->game->ub_current_time, all);
		}
		if (all->play->lttrs_cnt > all->game->memory && all->states->ub_count)
			all->states->undefined_behavior = 1;
		while (++index < all->play->lttrs_cnt)
			if ((letters[index] != all->play->letter_colected[index]))
				return ;
	}
	if (all->play->lttrs_cnt == 4 && all->states->undefined_behavior == 0)
		all->states->right_letters = 1;	
}