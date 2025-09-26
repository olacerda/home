/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_backup4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:16 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/24 23:42:25 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("\n\nCHECK RECTANGLE\n\nmap1len: %d\n", line_1_size);
	while (line < s_map->total_lines|| s_map->map[line] != NULL)
	{
		line_size = strlength(s_map->map[line]);
		printf("mapslens: %d\n", line_size);
		if (line_size != line_1_size)
			return (0);
		line++;
	}
	s_map->line_len = line_1_size;
	printf("\nLine_Len %d\n", s_map->line_len);
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
		if (line == 0 && (s_map->map[line][index] == '\n' || !s_map->map[line][index]))
		{
			index = 0;
			line = (s_map->total_lines - 1);
		}
	}
	line = 1;
	while(s_map->map[line] != NULL)
	{
		if ((s_map->map[line][0] != '1') || (s_map->map[line][s_map->line_len - 1] != '1'))
			return (0);
		line++;		
	}
	return (1);
}

// void create_elements(t_gameinfo *s_game)
// {
// 	char	*elements;
// 	int		*count_elements;
// 	int		index;
// 	char	*string;

// 	index = 0;
// 	string = "PEC10RXITO";
// 	elements = malloc(11 * sizeof(char));
// 	count_elements = malloc(11 * (sizeof(int)));
// 	if (!elements || !count_elements)
// 		return ;
// 	while (index < 11)
// 	{
// 		elements[index] = string[index];
// 		count_elements[index] = 0;
// 		index++;
// 	}
// 	s_game->elements = elements;
// 	s_game->count_elements = count_elements;
// }

void create_elements(t_gameinfo *s_game)
{
	t_element	*elements;
	// int		*count_elements;
	int		index;
	char	*string;

	index = 0;
	string = "PEC10RXITO";
	elements = malloc(11 * sizeof(t_element));
	if (!elements)
		return ;
	while (index < 11)
	{
		elements[index].charr = string[index];
		elements[index].count = 0;
		elements[index].line = 0;
		elements[index].column = 0;
		elements[index].px_column = 0;
		elements[index].px_line = 0;
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
	// (void)s_play;
	while (s_map->map[++line] != NULL)
	{
		column = -1;
		while ((s_map->map[line][++column]) && s_map->map[line][column] != '\n')
		{
			if (s_map->map[line][column] == 'P')
				*s_play = (t_playerinfo){line, column, 0, 0, 0, {0}, line * 64, column * 64, 0, 0, '\0', '\0', '\0', '\0'};
			if (s_map->map[line][column] == 'E')
			{
				s_game->e_line = line;
				s_game->e_column = column;
			}
			index = 0;
			while ((s_map->map[line][column] != s_game->element[index].charr) 
				&& (s_game->element[index].charr != 'O'))
				index++;				
			s_game->element[index].count++;
		}
	}
}

// void	get_element_positions(t_all *all)
// {
// 	int	line;
// 	int	column;
// 	int	index;

// 	line = 0;
// 	while (all->map->map[line] != NULL)
// 	{
// 		column = 0;
// 		while ((all->map->map[line][column] != '\n') && (all->map->map[line][column] != '\0'))
// 		{
// 			index = 0;
// 			// write(1, "AQUI 1\n", 7);
// 			while ((all->game->element[index].charr != all->map->map[line][column]) && (all->game->element[index].charr != 'O'))
// 			{
// 				// write(1, "AQUI 2\n", 7);
// 				index++;				
// 			}
// 			all->game->element[index].line = line;
// 			all->game->element[index].column = column;
// 			column++;
// 		}
// 		line++;
// 	}
// }

int	check_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
{
	int	index;

	index = 0;
	printf("\nNao Criou elementos\n");
	create_elements(s_game);
	printf("\nCriou elementos\n");
	printf("Char da struct-> %c\nCount da struct-> %d\n\n", s_game->element[0].charr, s_game->element[0].count);
	count_elements(s_map, s_play, s_game);
	printf("\nContou os elementos\n");
	int	i;

	i = 0;
	while (i < 6)
	{
		printf("\nelement %c: %d\n", s_game->element[i].charr, s_game->element[i].count);
		i++;
	}
	while(s_game->element[index].charr != '\0')
	{
		if ((s_game->element[index].charr == 'P' || s_game->element[index].charr == 'E') 
			&& s_game->element[index].count > 1)
			return (0);
		if (s_game->element[index].charr == 'C' && s_game->element[index].count < 1)
			return (0);
		if (s_game->element[index].charr == 'O' && s_game->element[index].count > 0)
			return (0);
		index++;
	}
	return (1);
}

int	path_to_colectable(char **map, int	line, int column, int *colectables)
{
	if ((column == 0) || line == 0 || map[line] == NULL || 
		map[line][column] == '\n' || map[line][column] == '\0' || 
		map[line][column] == '7' || map[line][column] == '1')
		return (0);
	if (map[line][column] == 'C')
		(colectables[0])--;
	if (map[line][column] == 'E')
		(colectables[1])--;
	if (colectables[0] == 0 && colectables[1] == 0)
			return (1);
	map[line][column] = '7';
	if(path_to_colectable(map, line + 1, column, colectables) == 1)
		return (1);
	if(path_to_colectable(map, line, column + 1, colectables) == 1)
		return (1);
	if(path_to_colectable(map, line - 1, column, colectables) == 1)
		return (1);
	if(path_to_colectable(map, line, column - 1, colectables) == 1)
		return (1);
	return (0);
}

int	check_all_paths(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
{
	// char **map;
	int	line;
	int	column;
	int	path;
	int	to_colect[2];

	to_colect[0] = s_game->element[2].count;
	to_colect[1] = 1;
	line = s_play->line;
	column = s_play->column;
	printf("\nplayer position:\n\n\nLine: %d\nColumn: %d\n\n\n", s_play->line, s_play->column);
	// map = create_map(s_map);
	printf("\nNOVO BOROGODOOOOOOOOOO\n\n\nLine: %d\nColumn: %d\n\n\n", s_play->line, s_play->column);
	path = path_to_colectable(s_map->map, line, column, to_colect);
	free_map(s_map);
	s_map->map = create_map(s_map);
	return (path);
}

int	check_file_name(char *name)
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
