/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:11:33 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/13 22:21:41 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_rectangle(t_mapinfo *s_map)
{
	int	line_1_size;
	int	line_size;
	int	line;

	line = 0;
	if (!(*s_map->map) || !s_map->map)
		return (0);
	line_1_size = strlength(s_map->map[line++]);
	if (!line_1_size)
		return (0);
	while (line < s_map->total_lines || s_map->map[line] != NULL)
	{
		line_size = strlength(s_map->map[line]);
		if (line_size != line_1_size || !line_size)
			return (0);
		line++;
	}
	s_map->line_len = line_1_size;
	return (1);
}

int	check_close_walls(t_mapinfo *s_map)
{
	int	line;
	int	index;

	index = 0;
	line = 0;
	if (!s_map->map || !(s_map->map[index]))
		return (0);
	while (s_map->map[line][index] && s_map->map[line][index] != '\n')
	{
		if (s_map->map[line][index++] != '1')
			return (0);
		if (line == 0 && (s_map->map[line][index] == '\n'
			|| !s_map->map[line][index]))
		{
			index = 0;
			line = (s_map->total_lines - 1);
		}
	}
	line = 1;
	while (s_map->map[++line] != NULL)
		if ((s_map->map[line][0] != '1') || (s_map->map[line][s_map->line_len
				- 1] != '1'))
			return (0);
	return (1);
}

int	check_map_size(t_all *all)
{
	if (all->map->line_len < 3 || all->map->total_lines < 3)
		return (0);
	if (all->map->total_lines == 3 && all->map->line_len < 5)
		return (0);
	if (all->map->line_len == 3 && all->map->total_lines < 5)
		return (0);
	return (1);
}
