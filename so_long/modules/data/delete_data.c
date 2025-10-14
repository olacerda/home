/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:12:38 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/13 21:42:57 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void	free_map(char **map)
{
	int	line;

	line = 0;
	if (!map)
		return ;
	while (map[line] != NULL)
	{
		free(map[line]);
		line++;
	}
	free(map);
}

void	destroy_all_images1(void *mlx, t_all_images *images)
{
	if (images->grass_wall_sheet->st)
		mlx_destroy_image(mlx, images->grass_wall_sheet->st);
	if (images->let_sheet->st)
		mlx_destroy_image(mlx, images->let_sheet->st);
	if (images->red_let_sheet->st)
		mlx_destroy_image(mlx, images->red_let_sheet->st);
	if (images->terminal_sheet->st)
		mlx_destroy_image(mlx, images->terminal_sheet->st);
	if (images->player_sheet->st)
		mlx_destroy_image(mlx, images->player_sheet->st);
	if (images->player_sheet_mirror->st)
		mlx_destroy_image(mlx, images->player_sheet_mirror->st);
	if (images->speed_player->st)
		mlx_destroy_image(mlx, images->speed_player->st);
	if (images->speed_player_mirror->st)
		mlx_destroy_image(mlx, images->speed_player_mirror->st);
	if (images->exit_sheet->st)
		mlx_destroy_image(mlx, images->exit_sheet->st);
	if (images->wall->st)
		mlx_destroy_image(mlx, images->wall->st);
	if (images->grass->st)
		mlx_destroy_image(mlx, images->grass->st);
	if (images->collectable->st)
		mlx_destroy_image(mlx, images->collectable->st);
}

void	destroy_all_images2(void *mlx, t_all_images *images)
{
	if (images->f->st)
		mlx_destroy_image(mlx, images->f->st);
	if (images->i->st)
		mlx_destroy_image(mlx, images->i->st);
	if (images->r->st)
		mlx_destroy_image(mlx, images->r->st);
	if (images->a->st)
		mlx_destroy_image(mlx, images->a->st);
	if (images->y->st)
		mlx_destroy_image(mlx, images->y->st);
	if (images->player->st)
		mlx_destroy_image(mlx, images->player->st);
	if (images->exit->st)
		mlx_destroy_image(mlx, images->exit->st);
	if (images->color->st)
		mlx_destroy_image(mlx, images->color->st);
	if (images->blank_letter->st)
		mlx_destroy_image(mlx, images->blank_letter->st);
	if (images->background->st)
		mlx_destroy_image(mlx, images->background->st);
	if (images->nbr1->st)
		mlx_destroy_image(mlx, images->nbr1->st);
	if (images->nbr2->st)
		mlx_destroy_image(mlx, images->nbr2->st);
}

void	free_all_images1(t_all_images *images)
{
	if (images->grass_wall_sheet)
		free(images->grass_wall_sheet);
	if (images->let_sheet)
		free(images->let_sheet);
	if (images->red_let_sheet)
		free(images->red_let_sheet);
	if (images->terminal_sheet)
		free(images->terminal_sheet);
	if (images->player_sheet)
		free(images->player_sheet);
	if (images->player_sheet_mirror)
		free(images->player_sheet_mirror);
	if (images->speed_player)
		free(images->speed_player);
	if (images->speed_player_mirror)
		free(images->speed_player_mirror);
	if (images->exit_sheet)
		free(images->exit_sheet);
	if (images->grass)
		free(images->grass);
	if (images->wall)
		free(images->wall);
	if (images->collectable)
		free(images->collectable);
}

void	free_all_images2(t_all_images *images)
{
	if (images->player)
		free(images->player);
	if (images->f)
		free(images->f);
	if (images->i)
		free(images->i);
	if (images->r)
		free(images->r);
	if (images->a)
		free(images->a);
	if (images->y)
		free(images->y);
	if (images->blank_letter)
		free(images->blank_letter);
	if (images->color)
		free(images->color);
	if (images->background)
		free(images->background);
	if (images->nbr1)
		free(images->nbr1);
	if (images->nbr2)
		free(images->nbr2);
	if (images->exit)
		free(images->exit);
}
