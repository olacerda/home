/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:10:55 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 06:01:41 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	path_to_colectable(char **map, int line, int column, int *tool)
{
	if ((column != 0 || line <= 0 || map[line] != NULL
			|| map[line][column] != '\n' || map[line][column] != '\0')
		&& (tool[LIMIT] >= 0 && map[line][column] != tool[TARGET]
			&& (map[line][column] == 'f' || map[line][column] == 'i'
				|| map[line][column] == 'r' || map[line][column] == 'a')))
		tool[LIMIT]++;
	else if ((column == 0 || line <= 0 || map[line] == NULL || map[line][column
		] == '\n' || map[line][column] == '\0') || (map[line][column] != '0' &&
			map[line][column] != tool[TARGET] && map[line][column] != 'E' && map
				[line][column] != 'P' && map[line][column] != 'C'))
		return (0);
	if (map[line][column] == tool[TARGET])
		(tool[COUNT])--;
	if ((tool[COUNT]) == 0)
		return (1);
	map[line][column] = '7';
	if (path_to_colectable(map, line + 1, column, tool) == 1)
		return (1);
	if (path_to_colectable(map, line, column + 1, tool) == 1)
		return (1);
	if (path_to_colectable(map, line - 1, column, tool) == 1)
		return (1);
	if (path_to_colectable(map, line, column - 1, tool) == 1)
		return (1);
	return (0);
}

int	letters_path(t_all *all, t_gameinfo *s_game, char **map, char *elements)
{
	static char	ignore[6] = {'y', 0, 0, 0, 0, '\0'};
	int			tool[3];
	int			index;

	index = 0;
	tool[LIMIT] = 0;
	while (elements[index])
	{
		if (index == 0)
			change_y_position(all, map, 1);
		tool[TARGET] = s_game->element[indexor(&(elements[index]))].charr;
		tool[COUNT] = s_game->element[indexor(&(elements[index]))].count;
		if (!(all->states->bonus) || !(path_to_colectable(map,
					s_game->element[indexor("y")].line,
					s_game->element[indexor("y")].column, tool)))
			return (0);
		if (index == 0)
			change_y_position(all, map, -1);
		if ((tool[LIMIT] > 0) && (index != 0))
			tool[LIMIT] = -1;
		ignore[index + 1] = tool[TARGET];
		copy_map(all->map, map, ignore);
		index++;
	}
	return (1);
}

int	exit_colect_path(t_all *all, t_gameinfo *s_game, char **map, char *elements)
{
	static char	ignore[3] = {0, 0, '\0'};
	int			index;
	int			tool[3];

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
			exit(1);
		}
		copy_map(all->map, map, ignore);
		index++;
	}
	return (1);
}

void	change_y_position(t_all *all, char **map, int flag)
{
	int	line;
	int	column;

	line = all->game->element[indexor("y")].line;
	column = all->game->element[indexor("y")].column;
	line = line + flag;
	if (map[line][column] == '0' || map[line][column] == 'f'
		|| map[line][column] == 'i' || map[line][column] == 'r'
		|| map[line][column] == 'a' || map[line][column] == 'C'
		|| map[line][column] == '7' || map[line][column] == 'P')
	{
		all->game->element[indexor("y")].line = line;
	}
	else
	{
		all->states->bonus = 0;
	}
}

int	check_all_paths(t_all *all, t_gameinfo *s_game, t_states *states)
{
	char	**map;
	int		path;

	map = create_map(all->map, all);
	copy_map(all->map, map, "fire");
	path = exit_colect_path(all, s_game, map, "CE");
	if (!path)
	{
		write(2, "Error\nFailed due to invalid colectables or exit path\n", 49);
		end_game(all);
	}
	if (states->bonus == 1)
	{
		copy_map(all->map, map, "y");
		path = letters_path(all, s_game, map, "Pfira");
		if (!path)
		{
			states->bonus = 0;
		}
	}
	free_map(map);
	return (1);
}
