/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:14:28 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:54:37 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core_game.h"

void	move_right(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + yes) / 64][(col + yes + speed) / 64] != '1') &&
		 (map[(line + no) / 64][(col + yes + speed) / 64] != '1') &&
		 (map[(line + yes) / 64][(col + yes + speed) / 64] != 'Y') &&
		 (map[(line + no) / 64][(col + yes + speed) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_column += speed;
	}
	else if ((map[(line + yes) / 64][(col + yes + speed2) / 64] != '1') &&
		(map[(line + no) / 64][(col + yes + speed2) / 64] != '1') &&
		 (map[(line + yes) / 64][(col + yes + speed2) / 64] != 'Y') &&
		(map[(line + no) / 64][(col + yes + speed2) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_column += speed2;
	}
}

void	move_down(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + yes + speed) / 64][(col + yes) / 64] != '1') && 
		(map[(line + yes + speed) / 64][(col + no) / 64] != '1') &&
		(map[(line + yes + speed) / 64][(col + yes) / 64] != 'Y') && 
		(map[(line + yes + speed) / 64][(col + no) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_line += speed;
	}
	else if ((map[(line + yes + speed2) / 64][(col + yes) / 64] != '1') &&
		 (map[(line + yes + speed2) / 64][(col + no) / 64] != '1') &&
		 (map[(line + yes + speed2) / 64][(col + yes) / 64] != 'Y') &&
		 (map[(line + yes + speed2) / 64][(col + no) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_line += speed2;
	}
}

void	move_left(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + no) / 64][(col + no - speed) / 64] != '1') && 
		(map[(line + yes) / 64][(col + no - speed) / 64] != '1') &&
		(map[(line + no) / 64][(col + no - speed) / 64] != 'Y') && 
		(map[(line + yes) / 64][(col + no - speed) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_column -= speed;
	}
	else if ((map[(line + no) / 64][(col + no - speed2) / 64] != '1') &&
		 (map[(line + yes) / 64][(col + no - speed2) / 64] != '1') &&
		 (map[(line + no) / 64][(col + no - speed2) / 64] != 'Y') &&
		 (map[(line + yes) / 64][(col + no - speed2) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_column -= speed2;
	}
}

void	move_up(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + no - speed) / 64][(col + no) / 64] != '1') && 
		(map[(line + no - speed) / 64][(col + yes) / 64] != '1') && 
		(map[(line + no - speed) / 64][(col + no) / 64] != 'Y') && 
		(map[(line + no - speed) / 64][(col + yes) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_line -= speed;
	}
	else if ((map[(line + no - speed2) / 64][(col + no) /64] != '1') &&
		 (map[(line + no - speed2) / 64][(col + yes) / 64] != '1') && 
		 (map[(line + no - speed2) / 64][(col + no) /64] != 'Y') &&
		 (map[(line + no - speed2) / 64][(col + yes) / 64] != 'Y'))
	{
		all->game->element[indexor("P")].px_line -= speed2;
	}
}

void	move_player(t_all *all)
{
	int	yes;
	int	no;

	all->play->p_pixel_column = all->game->element[indexor("P")].px_column;
	all->play->p_pixel_line = all->game->element[indexor("P")].px_line;
	if (all->states->undefined_behavior == 1)
		redefine_behavior(all);
	yes = 63 * (all->game->speed > 0);
	no = 63 * (all->game->speed < 0);
	if (all->states->key_w == 1)
		move_up(all, yes, no);
	if (all->states->key_s == 1)
		move_down(all, yes, no);
	if (all->states->key_a == 1)
		move_left(all, yes, no);
	if (all->states->key_d == 1)
		move_right(all, yes, no);
	all->game->element[indexor("P")].column = 
		all->game->element[indexor("P")].px_column / 64;
	all->game->element[indexor("P")].line = 
		all->game->element[indexor("P")].px_line / 64;
}