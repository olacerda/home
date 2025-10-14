/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:11:57 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 00:42:00 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	create_elements(t_gameinfo *s_game)
{
	t_element	*elements;
	int			index;
	char		*string;

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

void	count_elements(t_mapinfo *s_map, t_gameinfo *s_game)
{
	int	line;
	int	column;
	int	index;

	line = -1;
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
		while (map->map[line][column] != '\n' && map->map[line][column] != '\0')
		{
			index = 0;
			while ((game->element[index].charr != map->map[line][column])
				&& (game->element[index].charr != 'O'))
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

int	check_elements(t_mapinfo *s_map, t_gameinfo *game, t_states *states)
{
	int	idx;

	idx = -1;
	create_elements(game);
	count_elements(s_map, game);
	get_element_positions(game, s_map);
	states->bonus = 1;
	while (++idx < game->elements_quantity)
	{
		if ((game->element[idx].charr == 'f' || game->element[idx].charr == 'i'
				|| game->element[idx].charr == 'r'
				|| game->element[idx].charr == 'a'
				|| game->element[idx].charr == 'y')
			&& game->element[idx].count != 1)
			states->bonus = 0;
		if ((game->element[idx].charr == 'P' || game->element[idx].charr == 'E')
			&& game->element[idx].count != 1)
			return (0);
		if (game->element[idx].charr == 'C' && game->element[idx].count < 1)
			return (0);
		if (game->element[idx].charr == 'O' && game->element[idx].count > 0)
			return (0);
	}
	return (1);
}
