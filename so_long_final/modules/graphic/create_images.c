/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:12:49 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 19:23:08 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "graphic.h"

t_image *sheet_initiator(t_all *all, char *adress, char charr, t_element *ele)
{
	t_image	*sheet;

	sheet = malloc(sizeof(t_image));
	if (!sheet)
	{
		write(2, "Error\nFailed to allocate image\n", 32);
		end_game(all);
	}
	sheet->st = mlx_xpm_file_to_image(all->mlx, 
		adress, &sheet->wide, &sheet->tall);
	(void)((sheet->st) && (sheet->img = mlx_get_data_addr(sheet->st, &sheet->bpp,
		&sheet->sizeline, &sheet->endian)));
	if (!sheet->img || !sheet->st)
	{
		write(2, "Error\nFailed to obtain img with mlx get data addr\n", 51);
		end_game(all);
	}
	if (charr != '\0')
	{
		ele[indexor(&charr)].img = sheet->img;	
		ele[indexor(&charr)].mlx = sheet->st;	
	}
	return (sheet);
}

t_image	*image_initiator(t_all *all, int size, char charr, t_element *elements)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	if (!image)
	{
		write(2, "Error\nFailed to alocate image\n", 31);
		end_game(all);
	}
	image->tall = TALL * size;
	image->wide = WIDE * size;
	image->st = mlx_new_image(all->mlx, image->wide, image->tall);
	if (charr != '\0' && image->st)
		elements[indexor(&charr)].mlx = image->st;
	(void)((image->st) && (image->img = mlx_get_data_addr(image->st, &image->bpp, 
		&image->sizeline, &image->endian)));
	if (!image->img || !image->st)
	{
		write(2, "Error\nFailed to obtain image infos with mlx\n", 45);
		end_game(all);
	}
	if (charr != '\0')
		elements[indexor(&charr)].img = image->img;
	return (image);
}

void	all_sheets_initiator(t_all_images *images, t_all *all)
{
	images->grass_wall_sheet = sheet_initiator(all, 
		"textures/wall_grass.xpm", 0, all->game->element);
	images->let_sheet = sheet_initiator(all, 
		"textures/letters.xpm", 0, all->game->element);
	images->terminal_sheet = sheet_initiator(all, 
		"textures/terminal.xpm", 0, all->game->element);
	images->red_let_sheet = sheet_initiator(all, 
		"textures/red_letters.xpm", 0, all->game->element);
	images->collectable = sheet_initiator(all,
		 "textures/meat.xpm", 'C', all->game->element);
	images->player_sheet = sheet_initiator(all, 
		"textures/player.xpm", 0, all->game->element);
	images->player_sheet_mirror = sheet_initiator(all, 
		"textures/player_mirror.xpm", 0, all->game->element);
	images->speed_player = sheet_initiator(all,
		 "textures/speed_player.xpm", 0, all->game->element);
	images->speed_player_mirror = sheet_initiator(all,
		 "textures/speed_player_mirror.xpm", 0, all->game->element);
	images->exit_sheet = sheet_initiator(all,
		 "textures/fire.xpm", 0, all->game->element);
}

t_all_images	*all_images_initiator(t_all *all)
{
	t_all_images *images;

	images = malloc(sizeof(t_all_images));
	if (!images)
	{
		write(2, "Error\nFailed to allocate struct images\n", 40);
		end_game(all);
	}
	all_sheets_initiator(images, all);
	images->F = image_initiator(all, 1, 'F', all->game->element);
	images->I = image_initiator(all, 1, 'I', all->game->element);
	images->R = image_initiator(all, 1, 'R', all->game->element);
	images->A = image_initiator(all, 1, 'A', all->game->element);
	images->Y = image_initiator(all, 1, 'Y', all->game->element);
	images->grass = image_initiator(all, 1, '0', all->game->element);
	images->wall = image_initiator(all, 1, '1', all->game->element);
	images->exit = image_initiator(all, 1, 'E', all->game->element);
	images->color = image_initiator(all, 1,'\0', all->game->element);
	images->blank_letter = image_initiator(all, 10, '\0', all->game->element);
	images->player = image_initiator(all, 1, 'P', all->game->element);
	images->background = image_initiator(all, 1, '\0', all->game->element);
	images->nbr1 = image_initiator(all, 1, '\0', all->game->element);
	images->nbr2 = image_initiator(all, 1, '\0', all->game->element);
	all_images_fill_buffers(images);
	return (images);
}