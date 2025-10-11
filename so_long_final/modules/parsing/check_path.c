/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:10:55 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:01:00 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "parsing.h"

int	path_to_colectable(char **map, int	line, int column, int *tool)
{
	if ((column != 0 || line <= 0 || map[line] != NULL || map[line][column]
		 != '\n' || map[line][column] != '\0') && (tool[LIMIT] >= 0 && 
		map[line][column] != tool[TARGET] && (map[line][column] == 'F' || 
		map[line][column] == 'I' || map[line][column] == 'R' || 
		map[line][column] == 'A')))
		tool[LIMIT]++;
	else if ((column == 0 || line <= 0 || map[line] == NULL || map[line][column]
		 == '\n' || map[line][column] == '\0') || (map[line][column] != '0' &&
		 map[line][column] != tool[TARGET] && map[line][column] != 'E' && 
		 map[line][column] != 'P' && map[line][column] != 'C'))
			return (0);
	if (map[line][column] == tool[TARGET])
		(tool[COUNT])--;
	if ((tool[COUNT]) == 0)
		return (1);
	map[line][column] = '7';
	if(path_to_colectable(map, line + 1, column, tool) == 1)
		return (1);
	if(path_to_colectable(map, line, column + 1, tool) == 1)
		return (1);
	if(path_to_colectable(map, line - 1, column, tool) == 1)
		return (1);
	if(path_to_colectable(map, line, column - 1, tool) == 1)
		return (1);
	return (0);
}

int	letters_path(t_all *all, t_gameinfo *s_game, char **map, char *elements)
{
	static char ignore[6] = {0, 0, 0, 0, 0, '\0'};
	int 		tool[3];
	int			index;	

	index = 0;
	tool[LIMIT] = 0;
	while (elements[index] != 'A')
	{
		tool[TARGET] = s_game->element[indexor(&(elements[index + 1]))].charr;
		ignore[index] = tool[TARGET];
		tool[COUNT] = s_game->element[indexor(&(elements[index]))].count;
		if (!(path_to_colectable(map, s_game->element[indexor("Y")].line, 
			s_game->element[indexor("Y")].column, tool)))
		{
			return (0);
		}
		if (tool[LIMIT] > 0)
			tool[LIMIT] = -1;
		copy_map(all->map, map, ignore);
		index++;
	}
	return (1);
}

int	exit_colect_path(t_all *all, t_gameinfo *s_game, char **map, char *elements)
{
	static	char ignore[3] = {0, 0, '\0'};
	int	index;
	int tool[3];

	index = 0;
	tool[LIMIT] = 0;
	while (elements[index] != '\0')
	{
		(tool[TARGET]) = s_game->element[indexor(&(elements[index]))].charr;
		ignore[index] = (tool[TARGET]);
		tool[COUNT] = s_game->element[indexor(&(elements[index]))].count;
		if (!(path_to_colectable(map, s_game->element[indexor("P")].line,
			 s_game->element[indexor("P")].column, tool)))
		{
			write(2, "Error\nFailed to get a valid path\n", 34);
			exit (1);
		}
		copy_map(all->map, map, ignore);
		index++;
	}
	return (1);
}

void	get_y_bottom_positions(t_all *all, char **map)
{
	int	line;
	int	column;

	line = -1;
	while (map[++line] != NULL)
	{
		column = -1;
		while (map[line][++column] != '\n' && map[line][column] != '\0')
		{
			if (map[line][column] == 'Y')
			{
				if (map[line + 1][column] == '0')
				{
					map[line][column] = '0';
					line++;
					map[line][column] = 'Y';
					
				}
				return ;
			}
		}
	}
	all->states->bonus = 0;
}

int	check_all_paths(t_all *all, t_gameinfo *s_game, t_states *states)
{
	char **map;
	int	path;

	map = create_map(all->map, all);
	copy_map(all->map, map, "FIRE");
	path = exit_colect_path(all, s_game, map, "CE");
	if (!path)
	{
		write(2, "Error\nFailed due to invalid colectables or exit path\n", 49);
		end_game(all);
	}
	if (states->bonus == 1)
	{
		get_y_bottom_positions(all, map);
		path = letters_path(all, s_game, map, "PYFIRA");
		if (!path)
		{
			states->bonus = 0;
		}
	}
	free_map(map);
	return (1);
}