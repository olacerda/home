/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_backup9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/23 23:54:28 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char *chosen_map)
{
	int	fd;
	int	count;
	char	*string;

	count = 0;
	fd = open(chosen_map, O_RDONLY);
	if (fd < 0)
		return (0);
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

char	*get_map_adress(char *chosen_map)
{
	char *adress;
	int	map_len;
	int	index;
	int	ad_index;

	if (!chosen_map)
		return (NULL);
	index = 0;
	ad_index = 0;
	map_len = strlength(chosen_map);
	adress = malloc((map_len + 5 + 1) * sizeof(char));
	if (!adress)
		return (NULL);
	adress[ad_index++] = 'm';
	adress[ad_index++] = 'a';
	adress[ad_index++] = 'p';
	adress[ad_index++] = 's';
	adress[ad_index++] = '/';
	while (chosen_map[index] != '\0')
	{
		adress[ad_index] = chosen_map[index];
		ad_index++;
		index++;
	}
	adress[ad_index] = '\0';
	// printf("Map adress in function: %s\n", adress);
	return (adress);
}

char **create_map(t_mapinfo *s_map)
{
	char	**map;
	int		line;
	int		fd;

	// printf("\nentrou no create_map\n");
	fd = open(s_map->map_adress, O_RDONLY);
	if (fd < 0)
		return (NULL);
	write(1, "passou", 6);
	// printf("\n LINES %d\n", s_map->total_lines);
	map = malloc ((s_map->total_lines + 1) * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	line = 0;
	while(line < s_map->total_lines)
		map[line++] = getnextline(fd);
	map[line] = NULL;
	close(fd);
	return (map);
}

void	free_map(t_mapinfo *map)
{
	int	line;

	line = 0;
	while (map->map[line] != NULL)
	{
		free(map->map[line]);
		line++;	
	}
	free(map->map);
}

void	so_long(t_mapinfo *s_map)
{
	int		count = 0;

	if (!s_map->map)
		return ;
	while (s_map->map[count] != NULL)
	{
		printf("%s\n", s_map->map[count]);
		count++;
	}
}

t_sheet *sheet_initiator(void *mlx, int	sprite_number)
{
	t_sheet	*sheet;

	sheet = malloc(sizeof(t_sheet));
	if (!sheet)
		return (NULL);
	if (sprite_number == 1)
		sheet->mlx_st = mlx_xpm_file_to_image(mlx, "textures/forest.xpm", &sheet->wide, &sheet->tall);
	if (sprite_number == 2)
		sheet->mlx_st = mlx_xpm_file_to_image(mlx, "textures/letters.xpm", &sheet->wide, &sheet->tall);	
	sheet->img = mlx_get_data_addr(sheet->mlx_st, &sheet->bpp, &sheet->sizeline, &sheet->endian);
	return (sheet);
}

t_image	*image_initiator(void *mlx, int wide, int tall)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->tall = tall;
	image->wide = wide;
	image->mlx_st = mlx_new_image(mlx, wide, tall);
	if (!image->mlx_st)
		return (NULL);
	image->img = mlx_get_data_addr(image->mlx_st, &image->bpp, &image->sizeline, &image->endian);
	if (!image->img)
		return (NULL);
	return (image);
}

void	sheet_to_image_convertor(t_sheet *src, t_image *dst, t_image *background, int sprite_column, int sprite_line)
{
	int	ints_per_line;
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	// int teste = 0;
	// int fundo = ((int *)src->img)[0];

	// printf("\nINT DO FUNDO: ---------> %d\n", fundo);
	ints_per_line = ((src->bpp * dst->wide) / 32);
	src_idx = ((dst->sizeline / 4) * (sprite_column - 1)) + ((src->sizeline / 4) * ((sprite_line - 1) * dst->tall));
	img_line = 0;
	dst_idx = 0;
	printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
	// if (src_idx > ((src->sizeline * src->tall) - (dst->sizeline * dst->tall)))
	// 	return ;
	(void)ints_per_line;
	while (img_line < dst->tall)
	{
		count = 0;
		while(count < 64)
		{
			// (void)background;
			if (((int *)src->img)[src_idx] == -16777216)
				((int *)dst->img)[dst_idx] = ((int *)background->img)[dst_idx];
				// teste++;
			else
				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
			dst_idx++;
			src_idx++;
			count++;
		}
		img_line++;
		src_idx = src_idx + ((src->sizeline / 4) - (count));
		// (img_line * src->sizeline) + (dst->sizeline * (sprite_line - 1));
	}
}

void	update_background(t_sheet *src, t_image *dst, t_image *background, int sprite_column, int sprite_line, t_playerinfo *play)
{
	int	ints_per_line;
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	int	grid_line = (play->pixel_line / 64) * 64;
	int	grid_column = (play->pixel_column / 64) * 64;
	
	int	difference_line = play->pixel_line - grid_line;
	int	difference_column = play->pixel_column - grid_column;
	
	// int	background_column = difference_column;
	// int	background_line = difference_line * (background->sizeline / 4);
	
	// int	background_index = (background_column + background_line);
	int	background_index = 0;

	// int	background_column_limit = (background_line + background->sizeline) / 4; // pode substituir primeira parte por "background_line"
	// int	background_line_limit = ((background->tall * (background->sizeline / 4)) - background_index);
	
	// int teste = 0;
	// int fundo = ((int *)src->img)[0];
	int bg_line = difference_column;
	int bg_column = difference_line;

	// printf("\nINT DO FUNDO: ---------> %d\n", fundo);
	
	ints_per_line = ((src->bpp * dst->wide) / 32);
	src_idx = ((dst->sizeline / 4) * (sprite_column - 1)) + ((src->sizeline / 4) * ((sprite_line - 1) * dst->tall));
	img_line = 0;
	dst_idx = 0;
	printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
	// if (src_idx > ((src->sizeline * src->tall) - (dst->sizeline * dst->tall)))
	// 	return ;
	// (void)ints_per_line;
	// while (img_line < dst->tall)
	// {
	// 	count = 0;
	// 	while(count < ints_per_line)
	// 	{
	// 		// (void)background;
	// 		if (((int *)src->img)[src_idx] == -16777216)
	// 			((int *)dst->img)[dst_idx] = ((int *)background->img)[background_index];
	// 			// teste++;
	// 		else
	// 			((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
	// 		background_index++;
	// 		dst_idx++;
	// 		src_idx++;
	// 		count++;
	// 		if (background_index >= background_column_limit)
	// 			background_index = background_line;
	// 	}
	// 	// background_index += background->sizeline / 4;
	// 	background_column_limit += background->sizeline / 4;
	// 	if (background_column_limit >= background_line_limit)
	// 		background_column_limit = (background->sizeline / 4);
	// 	if (background_index >= background_line_limit)
	// 		background_index = background_column;
	// 	img_line++;
	// 	background_line = (difference_line + img_line) * (background->sizeline / 4);
	// 	if (background_line >= background_line_limit - background->sizeline)
	// 		background_line = 0;
	// 	src_idx = src_idx + ((src->sizeline / 4) - (count));
	// 	// (img_line * src->sizeline) + (dst->sizeline * (sprite_line - 1));
	// }
	while (img_line < dst->tall)
	{
		count = 0;
		while (count < ints_per_line)
		{
			bg_line = (difference_column + count); // % background->wide
			if (bg_line >= background->wide)
				bg_line = bg_line - background->wide;
			bg_column = (difference_line + img_line); // % background->tall
			if (bg_column >= background->tall)
				bg_column = bg_column - background->tall;
			background_index = bg_column * (background->sizeline / 4) + bg_line;

			if (((int *)src->img)[src_idx] == -16777216)
				((int *)dst->img)[dst_idx] = ((int *)background->img)[background_index];
			else
				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];

			dst_idx++;
			src_idx++;
			count++;
		}
		img_line++;
		src_idx = src_idx + ((src->sizeline / 4) - count);
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

t_all_images	*all_images_initiator(void *mlx)
{
	t_all_images *images;

	images = malloc(sizeof(t_all_images));
	if (!images)
		return (NULL);
	images->grass_wall_sheet = sheet_initiator(mlx, 1);
	images->letters_sheet = sheet_initiator(mlx, 2);
	
	images->R = image_initiator(mlx, 64, 64);
	images->X = image_initiator(mlx, 64, 64);
	images->I = image_initiator(mlx, 64, 64);
	images->T = image_initiator(mlx, 64, 64);
	images->grass = image_initiator(mlx, 64, 64);
	images->wall = image_initiator(mlx, 64, 64);
	images->player = image_initiator(mlx, 64, 64);
	images->collectable = image_initiator(mlx, 64, 64);
	images->exit = image_initiator(mlx, 64, 64);
	
	sheet_to_image_convertor(images->grass_wall_sheet, images->wall, NULL, 1, 1);
	// color_image(images->grass, 65280);
	sheet_to_image_convertor(images->grass_wall_sheet, images->grass, NULL, 2, 1);
	sheet_to_image_convertor(images->letters_sheet, images->player, images->grass, 1, 6);
	color_image(images->collectable, 501000);
	color_image(images->exit, 0);
	sheet_to_image_convertor(images->letters_sheet, images->R, images->grass, 5, 3);
	sheet_to_image_convertor(images->letters_sheet, images->X, images->grass, 4, 7);
	sheet_to_image_convertor(images->letters_sheet, images->I, images->grass, 4, 4);
	sheet_to_image_convertor(images->letters_sheet, images->T, images->grass, 5, 6);
	// color_image(images->e, 255);
	// color_image(images->x, 16711680);
	// color_image(images->i, 65280);
	// color_image(images->t, 16776960);	
	return (images);
}

void	put_images(void *mlx, t_mapinfo *map, void *window, t_all_images *images)
{
	int	line;
	int	index;

	line = 0;
	index = 0;
	while(map->map[line] != NULL && (line < map->total_lines))
	{
		index = 0;
		while(map->map[line][index] != '\n' && (index < map->line_len))
		{
			if (map->map[line][index] == '0' || map->map[line][index] == 'E')
				mlx_put_image_to_window(mlx, window, images->exit->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == '1')
				mlx_put_image_to_window(mlx, window, images->wall->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'P')
				mlx_put_image_to_window(mlx, window, images->player->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'C')
				mlx_put_image_to_window(mlx, window, images->collectable->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'R')
				mlx_put_image_to_window(mlx, window, images->R->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'X')
				mlx_put_image_to_window(mlx, window, images->X->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'I')
				mlx_put_image_to_window(mlx, window, images->I->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'T')
				mlx_put_image_to_window(mlx, window, images->T->mlx_st, index * 64, line * 64);
			index++;
		}
		line++;
	}
}

void	update_images(void *mlx, void *window, t_all *all, int previous_pixel_column, int previous_pixel_line)
{
		// mlx_put_image(all->mlx, all->window, all->play->img, all->play->pixel_line, all->play->pixel_column);
	mlx_put_image_to_window(mlx, window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
	mlx_put_image_to_window(mlx, window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
}

void make_sound(long frequency)
{
	static	t_time time;
    static	long last = 0;
    long 	now;

    gettimeofday(&time, NULL);
    now = (time.tv_sec * 1000000) + time.tv_usec;
	if (now - last >= frequency)
	{
		write(1, "\a", 1);
		last = now;
	}
}

int	check_letters_colected(t_all *all)
{
	static int	position = 0;
	int			index;

	index = 0;
	all->play->letter_colected[position] = all->map->map[all->play->line][all->play->column];
	position++;
	printf("Letter sheet:  ");
	while (index < 4)
	{
		printf("%c", all->play->letter_colected[index]);
		// printf("%c", all->game->elements[index + 5]);
		if ((all->play->letter_colected[index] != all->game->elements[index + 5]))
			return (0);
		// printf("passou do return\n");
		index++;
	}
	write(1, "\n", 1);
	return (1);	
}

// //FUNCIONANDO
// void	update_player_range(t_all *all)
// {
// 	printf("Entrou no update_player_range ---------->>\n");
// 	all->play->tl_range = all->map->map[all->play->pixel_line / 64][all->play->pixel_column / 64];
// 	all->play->tr_range = all->map->map[all->play->pixel_line / 64][(all->play->pixel_column + 63) / 64];
// 	all->play->bl_range = all->map->map[(all->play->pixel_line + 63) / 64][all->play->pixel_column / 64];
// 	all->play->br_range = all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column + 63) / 64];
// 	printf("\n\ntl: %c\ntr: %c\nbl: %c\nbr: %c\n\n\n", all->play->tl_range, all->play->tr_range, all->play->bl_range, all->play->br_range);
// }

// substituir a adicao pelo numero "48" pra ver se consegue entrar um pouco na imagem antes de coletar ela
void	update_player_range(t_all *all)
{
	printf("Entrou no update_player_range ---------->>\n");
	all->play->tl_range = all->map->map[(all->play->pixel_line + 15) /64][(all->play->pixel_column + 15) / 64];
	all->play->tr_range = all->map->map[(all->play->pixel_line + 15) / 64][(all->play->pixel_column + 47) / 64];
	all->play->bl_range = all->map->map[(all->play->pixel_line + 47) / 64][(all->play->pixel_column + 15) / 64];
	all->play->br_range = all->map->map[(all->play->pixel_line + 47) / 64][(all->play->pixel_column + 47) / 64];
	printf("\n\ntl: %c\ntr: %c\nbl: %c\nbr: %c\n\n\n", all->play->tl_range, all->play->tr_range, all->play->bl_range, all->play->br_range);
}

void	update_range_image(t_all *all, int	line, int column)
{
	int	grid_pixel_line;
	int	grid_pixel_column;

	printf("entrou no update_range_image----------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	grid_pixel_line = line * 64;
	grid_pixel_column = column * 64;
	all->map->map[line][column] = '0';
	printf("Passou do map[location] = '0'\n\n");
	mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, grid_pixel_column, grid_pixel_line);
}

int	check_player_range(t_all *all, char element)
{
	printf("entrou no CHECK_PLAYER_RANGE----------->>>>>>>>>>>>>>>>>\n\n");
	if (all->play->tl_range == element)
	{
		update_range_image(all, (all->play->pixel_line / 64), (all->play->pixel_column / 64));
		return (1);
	}
	if (all->play->tr_range == element)
	{
		update_range_image(all, (all->play->pixel_line / 64), ((all->play->pixel_column + 63) / 64));
		return (1);
	}
	if (all->play->bl_range == element)
	{
		update_range_image(all, ((all->play->pixel_line + 63) / 64), (all->play->pixel_column / 64));
		return (1);
	}
	if (all->play->br_range == element)
	{
		update_range_image(all, ((all->play->pixel_line + 63) / 64), ((all->play->pixel_column + 63) / 64));
		return (1);
	}
	return (0);
}

void	update_game(t_all *all)
{
	if ((check_player_range(all, 'C') == 1) && (all->states->full_colectables == 0))
	{
		write(1, "\a", 1);
		all->play->colected++;
		if (all->play->colected >= all->game->count_elements[2])
			all->states->full_colectables = 1;
		// all->map->map[all->play->line][all->play->column] = '0';
	}
	if ((check_player_range(all, 'R') == 1) || 
		(check_player_range(all, 'X') == 1) || 
		(check_player_range(all, 'I') == 1) || 
		(check_player_range(all, 'T') == 1))
	{
		write(1, "\a", 1);
		if (check_letters_colected(all) == 1)
			all->states->right_letters = 1;
		// all->map->map[all->play->line][all->play->column] = '0';		
	}
	printf("\nCOLECTED: %d\n", all->play->colected);
	printf("Letter State: %d\nCoin State: %d\n\n", all->states->right_letters, all->states->full_colectables);
	printf("Todos coletaveis: %d\n\nLetras corretas: %d\n\n", all->states->full_colectables, all->states->right_letters);
	if (all->states->full_colectables == 1 && all->states->right_letters == 1)
	{
		mlx_put_image_to_window(all->mlx, all->window, all->images->exit->mlx_st, all->game->e_column * 64, all->game->e_line * 64);	
	}
	if (all->states->full_colectables == 1 && all->states->right_letters == 1 && all->map->map[all->play->line][all->play->column] == 'E')
	{
		all->states->full_colectables = 0;
		mlx_clear_window(all->mlx, all->window);
		mlx_destroy_window(all->mlx, all->window);
		exit (0);
	}
	mlx_do_sync(all->mlx);
}

// int	callback(int code, void *arg)
// {
// 	// (void)code;
// 	// (void)arg;
// 	static int	steps;
// 	t_all 		*all;

// 	if (code == 100 || code == 97 || code == 119 || code == 115)
// 		steps++;
// 	write(1, "Steps: ", 7);
// 	putnumber(steps);
// 	write(1, "\n", 1);
// 	all =(t_all *)arg;
// 	all->play->p_column = all->play->column;
// 	all->play->p_line = all->play->line;
// 	if (code == 100 && (all->map->map[all->play->line][all->play->column + 1] != '1'))
// 		all->play->column++;
// 	if (code == 97 && (all->map->map[all->play->line][all->play->column - 1] != '1'))
// 		all->play->column--;
// 	if (code == 119 && (all->map->map[all->play->line - 1][all->play->column] != '1'))
// 		all->play->line--;
// 	if (code == 115 && (all->map->map[all->play->line + 1][all->play->column] != '1'))
// 		all->play->line++;
// 	update_images(all->mlx, all->window, all);
// 	update_game(all);
// 	return (0);
// }

// int	callback(int code, void *arg)
// {
// 	// static int steps;
// 	t_all *all = (t_all *)arg;
// 	static int	previous_pixel_column;
// 	static int	previous_pixel_line;
// 	int speed = 64;

// 	previous_pixel_column = all->play->pixel_column;
// 	previous_pixel_line = all->play->pixel_line;
// 	(void)code;
// 	// if (code == 100 || code == 97 || code == 119 || code == 115)
// 	// 	steps++;
// 	// write(1, "Steps: ", 7);
// 	// putnumber(steps);
// 	// write(1, "\n", 1);
// // -------------------------------
// 	// while (code == 100)
// 	// {
// 		if ((all->states->key_d == 1) && (all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column + 63 + speed) / 64] != '1') 
// 			&& (all->map->map[all->play->pixel_line / 64][(all->play->pixel_column + 63 + speed) / 64] != '1'))
// 			// (code == 100 && all->map->map[(all->play->pixel_line + 64) / 64][(all->play->pixel_column + 64 + 10 - 1) / 64] != '1'))
// 			all->play->pixel_column += speed;
// 		else if ((all->states->key_d == 1) && (all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column + 63 + 1) / 64] != '1') && 
// 			(all->map->map[all->play->pixel_line / 64][(all->play->pixel_column + 63 + 1) / 64] != '1'))
// 			all->play->pixel_column += 1;
// 		// mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
// 		// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
// 	// }

// 	// esquerda
// 	// while (code == 97)
// 	// {
// 		if ((all->states->key_a == 1) && (all->map->map[(all->play->pixel_line) / 64][(all->play->pixel_column - speed) / 64] != '1') && 
// 			(all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column - speed) / 64] != '1'))
// 			// (code == 97 && all->map->map[(all->play->pixel_line + 64) / 64][(all->play->pixel_column - 10 - 1) / 64] != '1'))
// 			all->play->pixel_column -= speed;
// 		else if ((all->states->key_a == 1) && (all->map->map[(all->play->pixel_line) / 64][(all->play->pixel_column - 1) / 64] != '1') && 
// 			(code == 97 && all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column - 1) / 64] != '1'))
// 			all->play->pixel_column -= 1;
// 	// }
// 	// cima
// 	// while (code == 19)
// 	// {
// 		if ((all->states->key_w == 1) && (all->map->map[(all->play->pixel_line - speed) / 64][all->play->pixel_column / 64] != '1') &&
// 			(all->map->map[(all->play->pixel_line - speed) / 64][(all->play->pixel_column + 63) / 64] != '1'))
// 			// (code == 119 && all->map->map[(all->play->pixel_line - 10 - 1 + 64) / 64][all->play->pixel_column / 64] != '1'))
// 			all->play->pixel_line -= speed;
// 		else if ((all->states->key_w == 1) && (all->map->map[(all->play->pixel_line - 1) / 64][all->play->pixel_column / 64] != '1') &&
// 			(all->map->map[(all->play->pixel_line - 1) / 64][(all->play->pixel_column + 63) / 64] != '1'))
// 			all->play->pixel_line -= 1;		
// 	// }
// 	// baixo
// 	// while (code == 115)
// 	// {
// 		if ((all->states->key_s == 1) && (all->map->map[(all->play->pixel_line + 63 + speed) / 64][(all->play->pixel_column + 63) / 64] != '1') &&
// 				(all->map->map[(all->play->pixel_line + 63 + speed) / 64][all->play->pixel_column / 64] != '1'))
// 			// (code == 115 && all->map->map[(all->play->pixel_line + 64 + 10 - 1) / 64][all->play->pixel_column / 64] != '1'))
// 			all->play->pixel_line += speed;
// 		else if ((all->states->key_s == 1) && (all->map->map[(all->play->pixel_line + 63 + 1) / 64][(all->play->pixel_column + 63) / 64] != '1') &&
// 				(all->map->map[(all->play->pixel_line + 63 + 1) / 64][all->play->pixel_column / 64] != '1'))
// 			all->play->pixel_line += 1;		
// 	// }
// //-----------------------------
		
// 	// Atualiza o INDEX do player na MATRIZ!!
// 	all->play->column = all->play->pixel_column / 64;
// 	all->play->line = all->play->pixel_line / 64;

// 	// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
// 	// update_images(all->mlx, all->window, all, previous_pixel_column, previous_pixel_line);
// 	// mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
// 	// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
// 	update_player_range(all);
// 	update_game(all);                                               
// 	return (0);
// }

int	callback(int code, void *arg)
{
	// static int steps;
	t_all *all = (t_all *)arg;
	// static int	previous_pixel_column;
	// static int	previous_pixel_line;
	int speed = 2;

	all->play->p_pixel_column = all->play->pixel_column;
	all->play->p_pixel_line = all->play->pixel_line;
	(void)code;
	// if (code == 100 || code == 97 || code == 119 || code == 115)
	// 	steps++;
	// write(1, "Steps: ", 7);
	// putnumber(steps);
	// write(1, "\n", 1);
// -------------------------------
	// while (code == 100)
	// {
		if ((all->states->key_d == 1) && (all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column + 63 + speed) / 64] != '1') 
			&& (all->map->map[all->play->pixel_line / 64][(all->play->pixel_column + 63 + speed) / 64] != '1'))
			// (code == 100 && all->map->map[(all->play->pixel_line + 64) / 64][(all->play->pixel_column + 64 + 10 - 1) / 64] != '1'))
			all->play->pixel_column += speed;
		else if ((all->states->key_d == 1) && (all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column + 63 + 1) / 64] != '1') && 
			(all->map->map[all->play->pixel_line / 64][(all->play->pixel_column + 63 + 1) / 64] != '1'))
			all->play->pixel_column += 1;
		// mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
		// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
	// }

	// esquerda
	// while (code == 97)
	// {
		if ((all->states->key_a == 1) && (all->map->map[(all->play->pixel_line) / 64][(all->play->pixel_column - speed) / 64] != '1') && 
			(all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column - speed) / 64] != '1'))
			// (code == 97 && all->map->map[(all->play->pixel_line + 64) / 64][(all->play->pixel_column - 10 - 1) / 64] != '1'))
			all->play->pixel_column -= speed;
		else if ((all->states->key_a == 1) && (all->map->map[(all->play->pixel_line) / 64][(all->play->pixel_column - 1) / 64] != '1') && 
			(code == 97 && all->map->map[(all->play->pixel_line + 63) / 64][(all->play->pixel_column - 1) / 64] != '1'))
			all->play->pixel_column -= 1;
	// }
	// cima
	// while (code == 19)
	// {
		if ((all->states->key_w == 1) && (all->map->map[(all->play->pixel_line - speed) / 64][all->play->pixel_column / 64] != '1') &&
			(all->map->map[(all->play->pixel_line - speed) / 64][(all->play->pixel_column + 63) / 64] != '1'))
			// (code == 119 && all->map->map[(all->play->pixel_line - 10 - 1 + 64) / 64][all->play->pixel_column / 64] != '1'))
			all->play->pixel_line -= speed;
		else if ((all->states->key_w == 1) && (all->map->map[(all->play->pixel_line - 1) / 64][all->play->pixel_column / 64] != '1') &&
			(all->map->map[(all->play->pixel_line - 1) / 64][(all->play->pixel_column + 63) / 64] != '1'))
			all->play->pixel_line -= 1;		
	// }
	// baixo
	// while (code == 115)
	// {
		if ((all->states->key_s == 1) && (all->map->map[(all->play->pixel_line + 63 + speed) / 64][(all->play->pixel_column + 63) / 64] != '1') &&
				(all->map->map[(all->play->pixel_line + 63 + speed) / 64][all->play->pixel_column / 64] != '1'))
			// (code == 115 && all->map->map[(all->play->pixel_line + 64 + 10 - 1) / 64][all->play->pixel_column / 64] != '1'))
			all->play->pixel_line += speed;
		else if ((all->states->key_s == 1) && (all->map->map[(all->play->pixel_line + 63 + 1) / 64][(all->play->pixel_column + 63) / 64] != '1') &&
				(all->map->map[(all->play->pixel_line + 63 + 1) / 64][all->play->pixel_column / 64] != '1'))
			all->play->pixel_line += 1;		
	// }
//-----------------------------
		
	// Atualiza o INDEX do player na MATRIZ!!
	all->play->column = all->play->pixel_column / 64;
	all->play->line = all->play->pixel_line / 64;

	// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
	// update_images(all->mlx, all->window, all, previous_pixel_column, previous_pixel_line);
	// mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
	// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
	// mlx_do_sync(all->mlx);
	update_player_range(all);
	update_game(all);                                               
	return (0);
}

int	check_key_pressed(int	code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	printf("entrou no key pressed\n");
	if (code == 100)
		all->states->key_d = 1;
	if (code == 97)
		all->states->key_a = 1;
	if (code == 119)
		all->states->key_w = 1;
	if (code == 115)
		all->states->key_s = 1;
	// callback(code, all);
	return (0);
}

int	check_key_released(int code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	printf("entrou no key released\n");
	if (code == 100)
		all->states->key_d = 0;
	if (code == 97)
		all->states->key_a = 0;
	if (code == 119)
		all->states->key_w = 0;
	if (code == 115)
		all->states->key_s = 0;
	// callback(code, all);
	return (0);
}

// void	update_sprite(t_image src, t_image *background, t_image *player_sprite, t_playerinfo *play)
// {
// 	int	ints_per_line;
// 	int	img_line;
// 	int src_idx;
// 	int	dst_idx;
// 	int	count;
// 	// int teste = 0;
// 	// int fundo = ((int *)src->img)[0];

// 	// printf("\nINT DO FUNDO: ---------> %d\n", fundo);
// 	ints_per_line = ((src->bpp * dst->wide) / 32);
// 	src_idx = ((dst->sizeline / 4) * (sprite_column - 1)) + ((src->sizeline / 4) * ((sprite_line - 1) * dst->tall));
// 	img_line = 0;
// 	dst_idx = 0;
// 	printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
// 	// if (src_idx > ((src->sizeline * src->tall) - (dst->sizeline * dst->tall)))
// 	// 	return ;
// 	// (void)ints_per_line;
// 	while (img_line < dst->tall)
// 	{
// 		count = 0;
// 		while(count < ints_per_line)
// 		{
// 			// (void)background;
// 			if (((int *)src->img)[src_idx] == -16777216)
// 				((int *)dst->img)[dst_idx] = ((int *)background->img)[dst_idx];
// 				// teste++;
// 			else
// 				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
// 			dst_idx++;
// 			src_idx++;
// 			count++;
// 		}
// 		img_line++;
// 		src_idx = src_idx + ((src->sizeline / 4) - (count));
// 		// (img_line * src->sizeline) + (dst->sizeline * (sprite_line - 1));
// 	}
// }
//------------------------------------------------------------------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int game_loop(void *arg)
{
    t_all *all;

    all = (t_all *)arg;
	if (all->states->full_colectables == 1 && all->states->right_letters == 1)
		make_sound(500000);
	if (all->states->key_a != 0 || all->states->key_w != 0 || all->states->key_s != 0 || all->states->key_d != 0)
	{
		callback(1, all);
		update_background(all->images->letters_sheet, all->images->player, all->images->grass, 1, 6, all->play);
		mlx_put_image_to_window(all->mlx, all->window, all->images->exit->mlx_st, all->play->p_pixel_column, all->play->p_pixel_line);
		mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->play->pixel_column, all->play->pixel_line);
		mlx_do_sync(all->mlx);
		usleep(10000);
	}
    return (0);
}

void	game_initializer(t_mapinfo *s_map, t_all *all)
{
	t_all_images *images;
	all->mlx = mlx_init();
	if (!(all->mlx))
		exit (1);
	images = all_images_initiator(all->mlx);
	all->images = images;
	all->window = mlx_new_window(all->mlx, s_map->line_len * 64, s_map->total_lines * 64, s_map->map_name);
	if (!(all->window))
		exit (1);
	put_images(all->mlx, s_map, all->window, images);
	// mlx_key_hook(all->window, callback, all);
	// mlx_hook(all->window, 2, 0, check_key_pressed, all);
	// mlx_hook(all->window, 3, 0, check_key_released, all);
	mlx_hook(all->window, 2, 1L<<0, check_key_pressed, all);
	mlx_hook(all->window, 3, 1L<<1, check_key_released, all);
	mlx_loop_hook(all->mlx, game_loop, all);
	mlx_loop(all->mlx);
}

int	check_map_size(t_all *all)
{
	if (all->map->line_len < 3 || all->map->total_lines < 3)
		return (0);
	if (all->map->total_lines == 3 && all->map->line_len < 5)
		return (0);
	if (all->map->line_len == 3 && all->map->total_lines < 5)
		return (0);
	return (1);
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
	*s_play = (t_playerinfo){0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, '\0', '\0', '\0', '\0'};
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
	s_map->map = create_map(s_map);
	if (!(s_map->map))
		return (1);
	so_long(s_map);
	printf("\nPassou aqui\n");
	if (!check_rectangle(s_map))
		return (1);
	if (!check_close_walls(s_map))
		return (1);
	if (!check_elements(s_map, s_play, s_game))
		return (1);
	if (!check_all_paths(s_map, s_play, s_game))
		return (1);
	if (!check_map_size(all))
		return (1);
	game_initializer(s_map, all);
	free(s_map);
}

// compilar com
// cc -Wall -Wextra -Werror -I libft -I MiniLibX/minilibx-linux so_long.c libft/parcing.c libft/utils.c libft/getnextline.c -L MiniLibX/minilibx-linux -lmlx -lXext -lX11 -lm