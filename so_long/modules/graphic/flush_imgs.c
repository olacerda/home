/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_imgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:07 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 10:58:32 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "graphic.h"

void	put_images(t_all *all, t_mapinfo *mapst, t_element *ele, char **map)
{
	int	ln;
	int	column;

	ln = -1; 	
	while(map[++ln] != NULL && (ln < mapst->total_lines))
	{
		column = -1;
		while(map[ln][++column] != '\n' && (column < mapst->line_len))
		{
			mlx_put_image_to_window(all->mlx, all->window, 
				ele[indexor(&(map[ln][column]))].mlx, column * 64, ln * 64);
			if ((map[ln][column] == 'F' || map[ln][column] == 'I' ||
				map[ln][column] == 'R' || map[ln][column] == 'A' ||
				map[ln][column] == 'E'|| map[ln][column] == 'P') ||
				 (map[ln][column] == 'Y' && all->states->bonus == 0)) 
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
		all->map->map[line][elemet[indexor(&(let[idx]))].column] = 
			elemet[indexor(&(let[idx]))].charr;
		mlx_put_image_to_window(all->mlx, all->window, img_mlx, 
			elemet[indexor(&(let[idx]))].column * WIDE, line * TALL);
	}
	all->play->F = 0;
	all->play->I = 0;
	all->play->R = 0;
	all->play->A = 0;
}

int	rebuild_current_map(t_all *all)
{
	int		line;
	int		index;
	char 	**map;

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
					all->game->element[indexor(&(map[line][index]))].mlx, 
						index * 64, line * 64);
			}
			index++;
		}
		line++;
	}
	return (0);
}