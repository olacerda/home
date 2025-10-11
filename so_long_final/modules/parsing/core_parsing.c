/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:12:19 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:26:59 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "parsing.h"

int	count_lines(char *chosen_map, t_all *all)
{
	int	fd;
	int	count;
	char	*string;

	count = 0;
	fd = open(chosen_map, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nFailed to open map\n", 26);
		end_game(all);
	}
	string = "";
	while(string != NULL)
	{
		string = getnextline(fd);
		if (string != NULL)
			count++;
		free(string);
	}
	close(fd);
	return (count);
}

char **create_map(t_mapinfo *map, t_all *all)
{
	char	**matriz;
	int		line;
	int		fd;

	fd = open(map->map_adress, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nFailed to get map fd\n", 27);
		end_game(all);
	}
	matriz = malloc ((map->total_lines + 1) * sizeof(char *));
	if (!matriz)
	{
		write(2, "Error\nFailed map allocation\n", 29);
		close(fd);
		end_game(all);
	}
	line = -1;
	while(++line < map->total_lines)
		matriz[line] = getnextline(fd);
	matriz[line] = NULL;
	return (close(fd), matriz);
}

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
				if (map->map[line][index] == ignore[idx_ignore])
				{
					copy[line][index] = '0';
					break ;
				}
			}
			if (!(ignore[idx_ignore]))
				copy[line][index] = map->map[line][index];
			index++;
		}
		copy[line][index] = '\0';
		line++;
	}
}

int	parcing(char *argv1, t_all *all)
{
	if (!(check_map_ber_type(argv1)))
		return (0);
	all->map->map_name = argv1;
	all->map->map_adress = get_map_adress(argv1, all);
	if (!(all->map->map_adress))
		return (0);
	all->map->total_lines = count_lines(all->map->map_adress, all);
	if (!all->map->total_lines)
		return (0);
	all->map->map = create_map(all->map, all);
	if (!(all->map->map))
		return (0);
	if (!check_rectangle(all->map))
		return (0);
	if (!check_close_walls(all->map))
		return (0);
	if (!(check_elements(all->map, all->game, all->states)))
		return (0);
	if (!check_all_paths(all, all->game, all->states))
		return (0);
	if (!check_map_size(all))
		return (0);
	return (1);
}