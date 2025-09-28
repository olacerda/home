/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_letters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 23:22:43 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/26 00:06:38 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	letter_number(t_all *all, int line, int column)
{
	line = all->game->element
}

void	letras_aleatorias(void)
{
	long	now;
	// int	index;

	now = get_time();
	printf("%li\n", now);
	// index = 0;
	
}

int	main(int argc, char *argv[])
{
	t_all 			*all = malloc(sizeof(t_all));
	t_playerinfo	*s_play = malloc(sizeof(t_playerinfo));
	t_mapinfo		*s_map = malloc(sizeof(t_mapinfo));
	t_gameinfo		*s_game = malloc(sizeof(t_gameinfo));
	t_states		*states = malloc(sizeof(t_states));

	if (argc != 2)
		return (1);
	*s_map = (t_mapinfo){0, 0, 0, 0, 0};
	*s_play = (t_playerinfo){0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, '\0', '\0', '\0', '\0', 0, 0, 0, 0};
	*s_game = (t_gameinfo){0, 0, 0, 0, 0};
	*states = (t_states){0, 0, 0, 0, 0, 0};
	all->map = s_map;
	all->play = s_play;
	all->game = s_game;
	all->states = states;
	if (!(check_file_name(argv[1])))
		return (1);
	s_map->map_name = argv[1];
	s_map->map_adress = get_map_adress(argv[1]);
	if (!(s_map->map_adress))
		return (1);
	s_map->total_lines = count_lines(s_map->map_adress);
	if (!s_map->total_lines)
		return (1);
	// write(1, "teste\n", 6);
	s_map->map = create_map(s_map);
	if (!(s_map->map))
		return (1);
	int line = 0;
	int column = 0;
	while (all->map->map[line] != NULL)
	{
		column = 0;
		while (all->map->map[line][column] != '\0')
		{
			printf("%c", all->map->map[line][column]);
			column++;
		}
		line++;
	}
	int check = 0;
	
	check = check_elements(s_map, s_play, s_game);
	printf("\n\n\nCheck ---> %d\n", check);
	if (!check)
	{
		return (1);
	}
	letras_aleatorias();
	// printf()
}