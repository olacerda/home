/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:16 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/06 19:08:47 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

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
	while (line < s_map->total_lines|| s_map->map[line] != NULL)
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
	while(s_map->map[line][index] && s_map->map[line][index] != '\n')
	{
		if(s_map->map[line][index++] != '1')
			return (0);
		if (line == 0 && (s_map->map[line][index] == '\n' || 
			!s_map->map[line][index]))
		{
			index = 0;
			line = (s_map->total_lines - 1);
		}
	}
	line = 1;
	while(s_map->map[++line] != NULL)
		if ((s_map->map[line][0] != '1') || 
			(s_map->map[line][s_map->line_len - 1] != '1'))
			return (0);	
	return (1);
}

void create_elements(t_gameinfo *s_game)
{
	t_element	*elements;
	int		index;
	char	*string;

	index = 0;
	string = s_game->real_elements;
	elements = malloc((s_game->elements_quantity) * sizeof(t_element));
	if (!elements)
		return ;
	while (index < s_game->elements_quantity)
	{
		elements[index].charr = string[index];
		elements[index].count = 0;
		elements[index].line = 0;
		elements[index].column = 0;
		elements[index].px_column = 0;
		elements[index].px_line = 0;
		elements[index].mlx = 0;
		elements[index].img = 0;
		index++;
	}
	s_game->element = elements;
}

void	count_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
{
	int	line;
	int	column;
	int	index;

	line = -1;
	(void)s_play;
	while (s_map->map[++line] != NULL)
	{
		column = -1;
		while ((s_map->map[line][++column]) && s_map->map[line][column] != '\n')
		{
			index = 0;
			while ((s_map->map[line][column] != s_game->element[index].charr) 
				&& (s_game->element[index].charr != 'O'))
				index++;				
			s_game->element[index].count++;
		}
	}
}

void	get_element_positions(t_gameinfo *game, t_mapinfo *map)
{
	int	line;
	int	column;
	int	index;

	line = 0;
	while (map->map[line] != NULL)
	{
		column = 0;
		while ((map->map[line][column] != '\n') && (map->map[line][column] != '\0'))
		{
			index = 0;
			while ((game->element[index].charr != map->map[line][column]) && (game->element[index].charr != 'O'))
			{
				index++;				
			}
			game->element[index].line = line;
			game->element[index].column = column;
			game->element[index].px_line = line * 64;
			game->element[index].px_column = column * 64;
			column++;
		}
		line++;
	}
}

int	check_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game, t_states *states)
{
	int	index;

	index = -1;
	create_elements(s_game);
	count_elements(s_map, s_play, s_game);
	get_element_positions(s_game, s_map);
	states->bonus = 1;
	while(++index < s_game->elements_quantity)
	{
		if ((s_game->element[index].charr == 'R' || s_game->element[index].charr == 'X' ||
			s_game->element[index].charr == 'I' || s_game->element[index].charr == 'T' ||
			s_game->element[index].charr == 'Y')
			&& s_game->element[index].count != 1)
			states->bonus = 0;
		if ((s_game->element[index].charr == 'P' && s_game->element[index].charr != 'E')
			&& s_game->element[index].count != 1)
			return (0);
		if (s_game->element[index].charr == 'C' && s_game->element[index].count < 1)
			return (0);
		if (s_game->element[index].charr == 'O' && s_game->element[index].count > 0)
			return (0);
	}
	return (1);
}

// int	check_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game, t_states *states)
// {
// 	int	index;

// 	index = -1;
// 	create_elements(s_game);
// 	count_elements(s_map, s_play, s_game);
// 	get_element_positions(s_game, s_map);
// 	states->bonus = 1;
// 	while(s_game->element[++index].charr != '\0')
// 	{
// 		if ((s_game->element[index].charr == 'R' || s_game->element[index].charr == 'X' ||
// 			s_game->element[index].charr == 'I' || s_game->element[index].charr == 'T' ||
// 			s_game->element[index].charr == 'Y')
// 			&& s_game->element[index].count != 1)
// 			states->bonus = 0;
// 		if ((s_game->element[index].charr == 'P' && s_game->element[index].charr != 'E')
// 			&& s_game->element[index].count != 1)
// 			return (0);
// 		if (s_game->element[index].charr == 'C' && s_game->element[index].count < 1)
// 			return (0);
// 		if (s_game->element[index].charr == 'O' && s_game->element[index].count > 0)
// 			return (0);
// 	}
// 	return (1);
// }

void	copy_map(t_mapinfo *map, char **copy, char *ignore)
{
	int	line;
	int	index;
	int	idx_ignore;

	line = 0;
	while (map->map[line] != NULL)
	{
		index = 0;
		while (map->map[line][index] != '\0')
		{
			idx_ignore = -1;
			while (ignore[++idx_ignore])
			{
				if (map->map[line][index] != ignore[idx_ignore])
					copy[line][index] = map->map[line][index];
				else
					copy[line][index] = '0';	
			}
			index++;
		}
		copy[line][index] = '\0';
		line++;
	}
	// line = -1;
	// while (copy[++line] != NULL)
	// 	printf("Copy map -> %s\n", copy[line]);
}

int	path_to_colectable(char **map, int	line, int column, char	to_colect, int *count)
{
	if (((column == 0) || line == 0 || map[line] == NULL || 
		map[line][column] == '\n' || map[line][column] == '\0' || 
		map[line][column] == '7' || map[line][column] == '1') || 
		((map[line][column] != '0') && (map[line][column] != (to_colect)) && map[line][column] != 'E' &&
			map[line][column] != 'P' && map[line][column] != 'Y'))
		return (0);
	if (map[line][column] == to_colect)
	{
		(*count)--;
	}
	if (*count == 0)
		return (1);
	map[line][column] = '7';
	if(path_to_colectable(map, line + 1, column, to_colect, count) == 1)
		return (1);
	if(path_to_colectable(map, line, column + 1, to_colect, count) == 1)
		return (1);
	if(path_to_colectable(map, line - 1, column, to_colect, count) == 1)
		return (1);
	if(path_to_colectable(map, line, column - 1, to_colect, count) == 1)
		return (1);
	return (0);
}

int	exit_colectables_path(t_mapinfo *s_map, t_gameinfo *s_game, char **map, char *elements)
{
	int	path;
	int	index;
	index = 0;
	char	target = s_game->element[indexor(&(elements[index]))].charr;
	int	count = s_game->element[indexor(&(elements[index]))].count;
	static	char ignore[3] = {0, 0, '\0'};

	path = 0;
	while (elements[index] != '\0')
	{
		target = s_game->element[indexor(&(elements[index]))].charr;
		ignore[index] = target;
		count = s_game->element[indexor(&(elements[index]))].count;
		path = path_to_colectable(map, s_game->element[indexor("P")].line, s_game->element[indexor("P")].column, target, &count);
		copy_map(s_map, map, ignore);
		if (!path)
			return (0);
		index++;
	}
	return (1);
}

int	letters_path(t_mapinfo *s_map, t_gameinfo *s_game, char **map, char *elements)
{
	int	path;
	int	index;
	index = 0;
	char	target = s_game->element[indexor(&(elements[index]))].charr;
	int	count = s_game->element[indexor(&(elements[index]))].count;
	static char ignore[6] = {0, 0, 0, 0, 0, '\0'};

	path = 0;
	while (elements[index] != 'T')
	{
		target = s_game->element[indexor(&(elements[index + 1]))].charr;
		ignore[index] = target;
		count = s_game->element[indexor(&(elements[index]))].count;
		path = path_to_colectable(map, s_game->element[indexor(&(elements[index]))].line, s_game->element[indexor(&(elements[index]))].column, target, &count);
		copy_map(s_map, map, ignore);
		if (!path)
			return (0);
		index++;
	}
	return (1);
}

int	check_all_paths(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game, t_states *states)
{
	char **map;
	int	path;

	(void)s_play;
	map = create_map(s_map);
	path = exit_colectables_path(s_map, s_game, map, "CE");
	if (!path)
		return (0);
	if (states->bonus == 1)
	{
		path = letters_path(s_map, s_game, map, "YRXIT");
		if (!path)
			return (0);	
	}
	free_map(map);
	return (path);
}

int	check_map_ber_type(char *name)
{
	char	*file_type;
	int		f_index;
	int		index;

	index = 0;
	f_index = -1;
	file_type = ".ber";
	if (!name)
		return (0);
	while (name[index] != '\0')
		index++;
	if (index < 5)
		return (0);
	index -= 4;      
	while ((file_type[++f_index] == name[index]) && (file_type[f_index]))
		index++;
	if (file_type[f_index] == '\0')
		return (1);
	return (0);
}
