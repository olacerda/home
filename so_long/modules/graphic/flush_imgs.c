/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_imgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:07 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 00:42:00 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic.h"

void	put_images(t_all *all, t_mapinfo *mapst, t_element *ele, char **map)
{
	int	ln;
	int	column;

	ln = -1;
	while (map[++ln] != NULL && (ln < mapst->total_lines))
	{
		column = -1;
		while (map[ln][++column] != '\n' && (column < mapst->line_len))
		{
			mlx_put_image_to_window(all->mlx, all->window,
				ele[indexor(&(map[ln][column]))].mlx, column * 64, ln * 64);
			if ((map[ln][column] == 'f' || map[ln][column] == 'i'
					|| map[ln][column] == 'r' || map[ln][column] == 'a'
					|| map[ln][column] == 'E' || map[ln][column] == 'P')
				|| (map[ln][column] == 'y' && all->states->bonus == 0))
			{
				all->map->map[ln][column] = '0';
				mlx_put_image_to_window(all->mlx, all->window,
					all->game->element[indexor("0")].mlx, column * 64, ln * 64);
			}
		}
	}
}

void	put_letter(t_all *all, char *let, char (*writed)[33], t_element *elemet)
{
	int		idx;
	int		line;
	void	*img_mlx;

	if (all->states->won == 1)
	{
		error_message(all, &all->terminal->wr_line, writed, 1);
		return ;
	}
	idx = -1;
	while (let[++idx])
	{
		line = elemet[indexor(&(let[idx]))].line;
		img_mlx = elemet[indexor(&(let[idx]))].mlx;
		all->map->map[line][elemet[indexor(&(let[idx]))].column] = elemet[
			indexor(&(let[idx]))].charr;
		mlx_put_image_to_window(all->mlx, all->window, img_mlx,
			elemet[indexor(&(let[idx]))].column * WIDE, line * TALL);
	}
	all->play->f = 0;
	all->play->i = 0;
	all->play->r = 0;
	all->play->a = 0;
}

int	rebuild_current_map(t_all *all)
{
	int		line;
	int		index;
	char	**map;

	line = 0;
	index = 0;
	map = all->map->map;
	mlx_clear_window(all->mlx, all->window);
	while (map[line] != NULL)
	{
		index = 0;
		while ((map[line][index] != '\n') && (map[line][index] != '\0'))
		{
			if (map[line][index] != 'P')
			{
				mlx_put_image_to_window(all->mlx, all->window,
					all->game->element[indexor(&(map[line][index]))].mlx, index
					* 64, line * 64);
			}
			index++;
		}
		line++;
	}
	return (0);
}
