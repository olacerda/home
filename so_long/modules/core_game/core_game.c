/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:13:40 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 05:48:10 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_game.h"

void	general_settings(t_all *all)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	all->game->speed = 2;
	all->game->speed2 = 1;
	all->game->usleep = 25000;
	all->game->shadow = 0;
	all->game->ub_time = 20;
	if (all->images && all->images->background && all->images->background->img)
		all->images->background->img = all->images->grass->img;
	all->game->usleep_save = all->game->usleep;
	all->game->real_elements = "PEC10firayO";
	all->game->ub_current_time = all->game->ub_time + 1;
	if (flag == 1)
	{
		while (all->game->real_elements[count])
			count++;
		all->game->elements_quantity = count;
		indexor(all->game->real_elements);
		flag = 0;
	}
}

void	update_images(t_all *all, int p_col, int p_line)
{
	int		col;
	int		line;
	void	*bg_mlx;
	void	*play_mlx;

	play_mlx = all->images->player->st;
	bg_mlx = all->images->color->st;
	col = all->game->element[indexor("P")].px_column;
	line = all->game->element[indexor("P")].px_line;
	update_animation_frames(all, all->game->usleep_save);
	exit_animation(all);
	player_animation(all);
	if (all->game->shadow == 1 && p_col != 0 && p_line != 0)
		mlx_put_image_to_window(all->mlx, all->window, bg_mlx, p_col, p_line);
	mlx_put_image_to_window(all->mlx, all->window, play_mlx, col, line);
	update_step_and_memory(all, 0);
	mlx_do_sync(all->mlx);
}

int	game_loop(void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	if (all->states->terminal == 1)
		open_terminal(all);
	if (all->states->undefined_behavior == 1)
	{
		if (all->states->sound == 1)
			make_sound(110000);
		ub_count(all);
	}
	if ((all->states->key_a != 0 || all->states->key_w != 0
			|| all->states->key_s != 0 || all->states->key_d != 0)
		&& all->states->terminal == 0)
	{
		all->play->movement = 1;
		move_player(all);
		check_player_range(all, '0');
	}
	else
		all->play->movement = 0;
	update_game(all);
	update_images(all, all->play->p_pixel_column, all->play->p_pixel_line);
	usleep(all->game->usleep);
	return (0);
}

void	game_initializer(t_all *all)
{
	t_all_images	*images;

	all->mlx = mlx_init();
	all->window = mlx_new_window(all->mlx, all->map->line_len * 64,
			all->map->total_lines * 64, all->map->map_name);
	if (!all->window)
	{
		write(2, "Error\nFailed to create mlx structures\n", 38);
		end_game(all);
	}
	images = all_images_initiator(all);
	all->images = images;
	get_username_and_pcnumber(all, 0, 0);
	all->window_terminal = NULL;
	general_settings(all);
	put_images(all, all->map, all->game->element, all->map->map);
	mlx_hook(all->window, 2, 1L << 0, check_key_pressed, all);
	mlx_hook(all->window, 3, 1L << 1, check_key_released, all);
	mlx_loop_hook(all->mlx, game_loop, all);
	mlx_expose_hook(all->window, rebuild_current_map, all);
	mlx_hook(all->window, 17, 0, end_game, all);
	mlx_loop(all->mlx);
}
