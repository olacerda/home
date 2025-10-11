/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:12:58 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:36:08 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "graphic.h"

void	sheet_to_image(t_image *src, t_image *dst, t_image *background, int nbr)
{
	int src_idx;
	int	dst_idx;
	int	line;
	int	column;
	int	ints_per_line;

	ints_per_line = ((src->bpp * dst->wide) / 32);
	src_idx = ((dst->sizeline / 4) * (nbr % (src->wide / dst->wide))) + ((src->
		sizeline / 4) * ((nbr / (src->wide / dst->wide)) * dst->tall)) - 1;
	line = -1;
	dst_idx = 0;
	while (++line < dst->tall)
	{
		column = -1;
		while((++column < ints_per_line))
		{
			if (((int *)src->img)[++src_idx] == -16777216 || 
										((int *)src->img)[src_idx] == 16777215)
				((int *)dst->img)[dst_idx] = ((int *)background->img)[dst_idx];
			else
				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
			dst_idx++;	
		}
		src_idx = src_idx + ((src->sizeline / 4) - (column));
	}
}

void	color_image(t_image *image, int	flag)
{
	int	ints_per_line;
	int	img_line;
	int	index;
	int	count;

	ints_per_line = ((image->bpp * image->wide) / 32);
	img_line = 0;
	count = 0;
	index = 0;
	while (img_line < image->tall)
	{
		count = 0;
		while(count < ints_per_line)
		{
			((int *)image->img)[index++] = flag;
			count++;
		}
		img_line++;
	}
}

t_background	*calculate_vars(t_all *all, t_image *src, t_image *dst, int nbr)
{
	static t_background	var;
	int					px_column;
	int 				px_line;

	px_column = all->game->element[indexor("P")].px_column;
	px_line = all->game->element[indexor("P")].px_line;
	var.grid_column = ((px_column / 64) * 64);
	var.grid_line = ((px_line / 64) * 64);
	var.difference_column = px_column - var.grid_column;
	var.difference_line = px_line - var.grid_line;
	var.ints_per_line = ((src->bpp * all->images->player->wide) / 32);
	var.src_idx = ((dst->sizeline / 4) * (nbr % (src->wide / dst->wide))) + 
		((src->sizeline / 4) * ((nbr / (src->wide / dst->wide)) * dst->tall));
	var.bg_line = var.difference_column;
	var.bg_column = var.difference_line;
	var.img_line = 0;
	var.dst_idx = 0;
	var.bg_idx = 0;
	var.count = 0;
	var.play = all->images->player->img;
	return (&var);
}

void	update_bg(t_image *src, t_image *bg, t_all *all, int nbr)
{
	t_background *x;

	x = calculate_vars(all, src, all->images->player, nbr);
	while ((x->img_line) < all->images->player->tall)
	{
		x->count = -1;
		while (++(x->count) < x->ints_per_line)
		{
			x->bg_column = (x->difference_column + x->count) % WIDE;
			x->bg_line = (x->difference_line + x->img_line) % TALL;
			x->bg_idx = (x->bg_line * (all->images->grass->sizeline / 4))
				+ x->bg_column;
			if ((((int *)src->img)[x->src_idx] == -16777216) || 
					(((int *)src->img)[x->src_idx] == 16777215))
				{
					((int *)x->play)[x->dst_idx] = ((int *)bg->img)[x->bg_idx];
				}
			else
				((int *)x->play)[x->dst_idx] = ((int *)src->img)[x->src_idx];
			x->dst_idx++;
			x->src_idx++;
		}
		x->img_line++;
		x->src_idx = x->src_idx + ((src->sizeline / 4) - x->count);
	}
}

void	all_images_fill_buffers(t_all_images *images)
{
	sheet_to_image(images->grass_wall_sheet, images->background, NULL, 1);
	sheet_to_image(images->grass_wall_sheet, images->grass, NULL, 1);
	sheet_to_image(images->grass_wall_sheet, images->wall, NULL, 0);
	sheet_to_image(images->collectable, images->collectable, images->grass, 0);
	sheet_to_image(images->exit_sheet, images->exit, images->grass, 0);
	color_image(images->color, 0);
	color_image(images->blank_letter, 0);
	sheet_to_image(images->let_sheet, images->F, images->grass, 15);
	sheet_to_image(images->let_sheet, images->I, images->grass, 18);
	sheet_to_image(images->let_sheet, images->R, images->grass, 27);
	sheet_to_image(images->let_sheet, images->A, images->grass, 14);
	sheet_to_image(images->terminal_sheet, images->Y, images->grass, 0);
	sheet_to_image(images->player_sheet, images->player, images->grass, 13);
}