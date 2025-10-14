/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:50 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 09:42:04 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core_game.h"

void	update_player_range(t_all *all, int line, int column, char terminal)
{
	char	**map;
	int		lin;
	int 	col;
	void	*element_buff;

	map = all->map->map;
	element_buff = all->game->element[indexor(&(map[line][column]))].mlx;
	lin = line * WIDE;
	col = column * TALL;
	if (all->map->map[line][column] == 'Y' && (terminal))
	{
		if (all->states->key_enter == 1)
			all->states->terminal = 1;
		return;
	}
	if (all->map->map[line][column] != '1' && 
			all->map->map[line][column] != 'Y')
		mlx_put_image_to_window(all->mlx, all->window, element_buff, col, lin);
}

int	check_player_range(t_all *all, char element)
{
	int	line;
	int	column;

	line = all->game->element[indexor("P")].px_line;
	column = all->game->element[indexor("P")].px_column;
	if (all->map->map[(line - 4) / 64][(column - 4) / 64] != element)
		update_player_range(all, ((line - 4) / 64), ((column - 4) / 64), 'Y');
	if (all->map->map[(line - 4) / 64][(column + 67) / 64] != element)
		update_player_range(all, ((line - 4) / 64), ((column + 67) / 64), 'Y');
	if (all->map->map[(line + 67) / 64][(column - 4) / 64] != element)
		update_player_range(all, ((line + 67) / 64), ((column - 4) / 64), 0);
	if (all->map->map[(line + 67) / 64][(column + 67) / 64] != element)
		update_player_range(all, ((line + 67) / 64), ((column + 67) / 64), 0);
	if (all->map->map[(line - 4) / 64][(column + 32) / 64] != element)
		update_player_range(all, ((line - 4) / 64), ((column + 32) / 64), 'Y');
	if (all->map->map[(line + 32) / 64][(column + 67) / 64] != element)
		update_player_range(all, ((line + 32) / 64), ((column + 67) / 64), 0);
	if (all->map->map[(line + 67) / 64][(column + 32) / 64] != element)
		update_player_range(all, ((line + 67) / 64), ((column + 32) / 64), 0);
	if (all->map->map[(line + 32) / 64][(column - 4) / 64] != element)
		update_player_range(all, ((line + 32) / 64), ((column - 4) / 64), 0);
	return (0);
}

int	update_hitbox(t_all *all, int line, int column, char elment)
{
	int		px_line;
	int		px_col;
	void	*grass_mlx;

	grass_mlx = all->images->grass->st;
	px_line = line * 64;
	px_col = column * 64;
	if (all->map->map[line][column] == elment)
	{
		if (all->states->undefined_behavior != 1 && elment != 'Y')
			write(1, "\a", 1);
		if (elment == 'F' || elment == 'I' || elment == 'R' || elment == 'A')
			check_letters_colected(all, elment, line, column);
		if (((elment != 'Y') && (elment != 'E')))
		{
			all->map->map[line][column] = '0';
			mlx_put_image_to_window(all->mlx, all->window, grass_mlx, px_col, 
				px_line);
		}
		return (1);
	}
	return (0);
}

int	check_hitbox(t_all *all, char element)
{
	int	line;
	int	column;
	line = all->game->element[indexor("P")].px_line;
	column =  all->game->element[indexor("P")].px_column;
	if (update_hitbox(all, ((line + 8) / 64), ((column + 8) / 64), element))
		return (1);
	if (update_hitbox(all, ((line + 8) / 64), ((column + 50) / 64), element))
		return (1);
	if (update_hitbox(all, ((line + 54) / 64), ((column + 8) / 64), element))
		return (1);
	if (update_hitbox(all, ((line + 54) / 64), ((column + 50) / 64), element))
		return (1);
	return (0);
}