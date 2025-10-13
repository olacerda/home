/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:12:29 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 11:16:57 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "data.h"

//core_data.c --------
void			init_structures(t_all *all);
int				end_game(t_all *all);

void	init_structures(t_all *all)
{
	t_playerinfo	*play;
	t_mapinfo		*map;
	t_gameinfo		*game;
	t_states		*states;
	t_terminalinfo 	*terminal;

	play = malloc(sizeof(t_playerinfo));
	map = malloc(sizeof(t_mapinfo));
	game = malloc(sizeof(t_gameinfo));
	states = malloc(sizeof(t_states));
	terminal = malloc(sizeof(t_terminalinfo));
	if (!(all && play && map && game && states && terminal))
	{
		write(2, "Error\nFailed structure allocation\n", 34);
		end_game(all);
	}
	*map = (t_mapinfo){0, 0, 0, 0, 0};
	*play = (t_playerinfo){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, {0}};
	*game = (t_gameinfo){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	*states = (t_states){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		1, 1, 0, 1, 0, 0, 1};
	*terminal = (t_terminalinfo){0, 0, 0, 5, 0, 0, 0, 0, 5, {{0}}};
	*all = (t_all){map, play, 0, game, states, terminal, 0, 0, 0};
}

void	free_structures(t_all *all)
{
	if (all->images)
	{
		destroy_all_images1(all->mlx, all->images);
		destroy_all_images2(all->mlx, all->images);
		free_all_images1(all->images);
		free_all_images2(all->images);
		free(all->images);
	}
	if (all->game)
		free(all->game);
	if (all->map)
		free(all->map);
	if (all->play)
		free(all->play);
	if (all->states)
		free(all->states);
	if (all->terminal)
		free(all->terminal);
	if (all->mlx)
	{
		mlx_destroy_display(all->mlx);
		free(all->mlx);
	}
}

int	end_game(t_all *all)
{
	if (all->mlx)
		mlx_loop_end(all->mlx);
	if (all->window)
	{
		mlx_clear_window(all->mlx, all->window);
		mlx_destroy_window(all->mlx, all->window);
	}
	if (all->window_terminal)
		mlx_destroy_window(all->mlx, all->window_terminal);
	if (all->map->map)
		free_map(all->map->map);
	if (all->map->map_adress)
		free(all->map->map_adress);
	if (all->game->element)
		free(all->game->element);
	if (all->states->pc_number == 1 && all->terminal->user_pc_number)
		free(all->terminal->user_pc_number);
	if (all->states->user_name == 1 && all->terminal->user_name)
		free(all->terminal->user_name);
	free_structures(all);
	if (all)
		free(all);
	exit (1);
	return (0);
}