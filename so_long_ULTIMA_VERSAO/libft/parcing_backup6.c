/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_backup6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:32:16 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/26 23:20:15 by olacerda         ###   ########.fr       */
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
// real_elements
void create_elements(t_gameinfo *s_game)
{
	t_element	*elements;
	// int		*count_elements;
	int		index;
	char	*string;

	index = 0;
	// string = "PEC10RXITO";
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
			// if (s_map->map[line][column] == 'P')
			// 	*s_play = (t_playerinfo){line, column, 0, 0, 0, {0}, line * 64, column * 64, 0, 0, '\0', '\0', '\0', '\0', 0, 0, 0, 0};
			// if (s_map->map[line][column] == 'E')
			// {
			// 	s_game->e_line = line;
			// 	s_game->e_column = column;
			// }
			index = 0;
			while ((s_map->map[line][column] != s_game->element[index].charr) 
				&& (s_game->element[index].charr != 'O'))
				index++;				
			s_game->element[index].count++;
		}
	}
}
//indexor
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
			// write(1, "AQUI 1\n", 7);
			while ((game->element[index].charr != map->map[line][column]) && (game->element[index].charr != 'O'))
			{
				// write(1, "AQUI 2\n", 7);
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
// ATUALIZAR CHECK ELEMENTS PARA CONTAR COM "Y" TAMBEM
// int	check_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
// {
// 	int	index;

// 	index = 0;
// 	create_elements(s_game);
// 	count_elements(s_map, s_play, s_game);
// 	get_element_positions(s_game, s_map);
// 	while(s_game->element[index].charr != '\0')
// 	{
// 		if ((s_game->element[index].charr == 'P' || s_game->element[index].charr == 'E' || 
// 			s_game->element[index].charr == 'R' || s_game->element[index].charr == 'X' || 
// 			s_game->element[index].charr == 'I' || s_game->element[index].charr == 'T')
// 			&& s_game->element[index].count > 1)
// 			return (0);
// 		if (s_game->element[index].charr == 'C' && s_game->element[index].count < 1)
// 			return (0);
// 		if (s_game->element[index].charr == 'O' && s_game->element[index].count > 0)
// 			return (0);
// 		index++;
// 	}
// 	return (1);
// }


int	check_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
{
	int	index;

	index = 0;
	create_elements(s_game);
	count_elements(s_map, s_play, s_game);
	get_element_positions(s_game, s_map);
	while(s_game->element[index].charr != '\0')
	{
		if ((s_game->element[index].charr != '0' && s_game->element[index].charr != '1' &&
			s_game->element[index].charr != 'C' && s_game->element[index].charr != 'O')
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

void	copy_map(t_mapinfo *map, char **copy, char ignore)
{
	int	line;
	int	index;

	line = 0;
	printf("Copiou o mapa, colocando '0' no lugar de: %c\n\n", ignore);
	while (map->map[line] != NULL)
	{
		index = 0;
		while (map->map[line][index] != '\0')
		{
			if (map->map[line][index] != ignore)
				copy[line][index] = map->map[line][index];
			else
				copy[line][index] = '0';
			index++;
		}
		copy[line][index] = '\0';
		// printf("dentro de COPY map: %s", copy[line]);
		// printf("dentro de ORIGINAL: %s", map->map[line]);
		line++;
	}
	line = 0;
	while (copy[line++] != NULL)
		printf("Copy map -> %s\n", copy[line]);
	// map->map[line] = NULL;
}

// int	path_to_colectable(char **map, int	line, int column, char	*to_colect, int *count)
// {
// 	if (((column == 0) || line == 0 || map[line] == NULL || 
// 		map[line][column] == '\n' || map[line][column] == '\0') || 
// 		((map[line][column] != '0') && (map[line][column] != *to_colect)))
// 		return (0);
// 	if (map[line][column] == *to_colect)
// 	{
// 		(*count)--;
// 		printf("Coletavel: %c  Quantidade faltando: %d\n", *to_colect, *count);
// 	}
// 	if (*count == 0)
// 		return (1);
// 	map[line][column] = '7';
// 	if(path_to_colectable(map, line + 1, column, to_colect, count) == 1)
// 		return (1);
// 	if(path_to_colectable(map, line, column + 1, to_colect, count) == 1)
// 		return (1);
// 	if(path_to_colectable(map, line - 1, column, to_colect, count) == 1)
// 		return (1);
// 	if(path_to_colectable(map, line, column - 1, to_colect, count) == 1)
// 		return (1);
// 	return (0);
// }


int	path_to_colectable(char **map, int	line, int column, char	*to_colect, int *count)
{
	if (((column == 0) || line == 0 || map[line] == NULL || 
		map[line][column] == '\n' || map[line][column] == '\0' || 
		map[line][column] == '7' || map[line][column] == '1') || 
		((map[line][column] != '0') && (map[line][column] != (*to_colect)) && map[line][column] != 'E' &&
			map[line][column] != 'P'))
		return (0);
	if (map[line][column] == *to_colect)
	{
		(*count)--;
		printf("Coletavel: %c  Quantidade faltando: %d\n", *to_colect, *count);
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
	// int	line = 0;

	path = 0;
	printf("\nExit and Colectables Path----------------------------->>>>>>>>>>\n\n");
	while (elements[index] != '\0')
	{
		// write(1, "\n\n\n", 3);
		// while (map[line] != NULL)
		// {
		// 	// printf("COPY-> %s", map[line]);
		// 	line++;
		// }
		// line = 0;
		// write(1, "\n\n\n", 3);
		// while (s_map->map[line] != NULL)
		// {
		// 	// printf("ORIGINAL-> %s", map[line]);
		// 	line++;
		// }
		// write(1, "\n\n\n", 3);
		target = s_game->element[indexor(&(elements[index]))].charr;
		count = s_game->element[indexor(&(elements[index]))].count;
		path = path_to_colectable(map, s_game->element[indexor("P")].line, s_game->element[indexor("P")].column, &target, &count);
		printf("Path do char:%c  Quantidade: %d ->> %d\n\n", s_game->element[indexor(&(elements[index]))].charr, s_game->element[indexor(&(elements[index]))].count, path);
		copy_map(s_map, map, target);
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

	printf("\n\n ------------------------------------>>>>>>>>>>>>Letters path\n");
	path = 0;
	path = path_to_colectable(map, s_game->element[indexor("P")].line, s_game->element[indexor("P")].column, &target, &count);
	copy_map(s_map, map, target);
	printf("Path to char:%c to --> %c Quantidade: %d ->> %d\n\n", s_game->element[indexor("P")].charr, s_game->element[indexor(&(elements[index]))].charr, s_game->element[indexor(&(elements[index]))].count, path);
	if (!path)
		return (0);
	while (elements[index] != 'T')
	{
		target = s_game->element[indexor(&(elements[index + 1]))].charr;
		count = s_game->element[indexor(&(elements[index]))].count;
		path = path_to_colectable(map, s_game->element[indexor(&(elements[index]))].line, s_game->element[indexor(&(elements[index]))].column, &target, &count);
		copy_map(s_map, map, target);
		printf("Path to char:%c  to ->> %c  Quantidade: %d ->> %d\n\n", s_game->element[indexor(&(elements[index]))].charr, s_game->element[indexor(&(elements[index + 1]))].charr, s_game->element[indexor(&(elements[index]))].count, path);
		if (!path)
			return (0);
		index++;
	}
	return (1);
}

int	check_all_paths(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
{
	char **map;
	int	path;

	write(1, "test123\n", 8);
	(void)s_play;
	map = create_map(s_map);
	path = exit_colectables_path(s_map, s_game, map, "CE");
	printf("***   Primeiro path: %d   ***\n\n\n", path);
	if (!path)
		return (0);
	path = letters_path(s_map, s_game, map, "RXIT");
	printf("***   Segundo path: %d   ***\n\n\n\n", path);
	if (!path)
		return (0);	
	free_map(map);

	// printf("\nplayer position:\n\n\nLine: %d\nColumn: %d\n\n\n", s_play->line, s_play->column);
	// printf("\nNOVO BOROGODOOOOOOOOOO\n\n\nLine: %d\nColumn: %d\n\n\n", s_play->line, s_play->column);
	return (path);
}

// int	check_all_paths(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game)
// {
// 	// char **map;
// 	int	line;
// 	int	column;
// 	int	path;
// 	int	to_colect[2];

// 	to_colect[0] = s_game->element[2].count;
// 	to_colect[1] = 1;
// 	line = s_game->element[indexor("P")].line;
// 	column = s_game->element[indexor("P")].column;
// 	printf("\nplayer position:\n\n\nLine: %d\nColumn: %d\n\n\n", s_play->line, s_play->column);
// 	// map = create_map(s_map);
// 	printf("\nNOVO BOROGODOOOOOOOOOO\n\n\nLine: %d\nColumn: %d\n\n\n", s_play->line, s_play->column);
// 	path = path_to_colectable(s_map->map, line, column, to_colect);
// 	free_map(s_map);
// 	s_map->map = create_map(s_map);
// 	return (path);
// }


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
