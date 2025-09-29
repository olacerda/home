/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_backup17.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/28 03:12:07 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//printf
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

char	*copy_string(char *string)
{
	int	size;
	int	index;
	char *result;

	size = 0;
	index = 0;
	while (string[size])
		size++;
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (string[index])
	{
		result[index] = string[index];
		index++;
	}
	result[index] = '\0';
	return (result);
}

char **create_map(t_mapinfo *s_map)
{
	char	**map;
	int		line;
	int		fd;
	char	*string;

	fd = open(s_map->map_adress, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc ((s_map->total_lines + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	line = -1;
	while(++line < s_map->total_lines)
	{
		string = getnextline(fd);
		map[line] = copy_string(string);
		free(string);
	}
	map[line] = NULL;
	return (close(fd), map);
}

void	free_map(char **map)
{
	int	line;

	line = 0;
	while (map[line] != NULL)
	{
		free(map[line]);
		line++;	
	}
	free(map);
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
	// printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
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

void	update_background(t_sheet *src, t_image *dst, t_image *background, int sprite_column, int sprite_line, t_gameinfo *game)
{
	int	ints_per_line;
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	int	grid_line = (game->element[indexor("P")].px_line / 64) * 64;
	int	grid_column = (game->element[indexor("P")].px_column / 64) * 64;
	
	int	difference_line = game->element[indexor("P")].px_line - grid_line;
	int	difference_column = game->element[indexor("P")].px_column - grid_column;
	
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
	// printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
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
			bg_line = (difference_column + count);
			if (bg_line >= background->wide)
				bg_line = bg_line - background->wide;
			bg_column = (difference_line + img_line);
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
	images->color = image_initiator(mlx, 64, 64);
	images->blank_letter = image_initiator(mlx, 300, 30);
	
	sheet_to_image_convertor(images->grass_wall_sheet, images->wall, NULL, 1, 1);
	// color_image(images->grass, 65280);
	sheet_to_image_convertor(images->grass_wall_sheet, images->grass, NULL, 2, 1);
	sheet_to_image_convertor(images->letters_sheet, images->player, images->grass, 1, 6);
	color_image(images->collectable, 501000);
	color_image(images->exit, 0);
	color_image(images->color, 16711680);
	color_image(images->blank_letter, 0);
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
				mlx_put_image_to_window(mlx, window, images->background->mlx_st, index * 64, line * 64);
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
		// mlx_put_image(all->mlx, all->window, all->play->img, all->game->element[indexor("P")].px_line, all->game->element[indexor("P")].px_column);
	mlx_put_image_to_window(mlx, window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
	mlx_put_image_to_window(mlx, window, all->images->player->mlx_st, all->game->element[indexor("P")].px_column, all->game->element[indexor("P")].px_line);
}


long	get_full_time()
{
	t_time	time;
	long	now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000000) + time.tv_usec;
	return (now);
}

void make_sound(long frequency)
{
    static	long last = 0;
    long 	now;
	// static int	a = 3;
	// int	b;

	// b = 5;
    now = get_full_time();
	// if (a > 0)
	// {
	// 	if (now - last >= 1000000)
	// 	{
	// 		// write(1, "\a", 1);
	// 		// usleep(2000);
	// 		// write(1, "\a", 1);
	// 		last = now;
	// 	}
	// 	a--;		
	// }
	if (now - last >= frequency)
	{
		write(1, "\a", 1);
		last = now;
		// a = 3;
	}
}


// Criar uma funcao chamada "event_free", que "limpa" o buffer das letras coletadas, e "zera" o index "positions" de check_letters_colected IMPORTANTE ! ! ! ! ! ! ! ! ! ! ! !

void	check_letters_colected(t_all *all, char	element, int line, int column)
{
	int			index;
	char	*letters_colected;
	char *letters;
	int	position;

	letters_colected = all->play->letter_colected;
	position = 0;
	letters = "RXIT";
	index = 0;
	if (element == 'R' || element == 'X' || element == 'I' || element == 'T')
	{
		all->play->letter_colected[position] = all->map->map[line][column];
		position = ++all->play->letters_colected_amount;
		if (position > all->game->memory)
			all->states->undefined_behavior = 1;
		printf("Letter sheet:  ");
		while (index < position)
		{
			printf("%c", letters[index]);
			// printf("%c", all->game->element[index + 5].charr);
			if ((letters[index] != letters_colected[index]))
				return ;
			// printf("passou do return\n");
			index++;
		}
		write(1, "\n", 1);
	}
	if (all->play->letters_colected_amount == 4)
		all->states->right_letters = 1;	
}

// substituir a adicao pelo numero "48" pra ver se consegue entrar um pouco na imagem antes de coletar ela
void	update_player_range(t_all *all)
{
	printf("Entrou no update_player_range ---------->>\n");
	all->play->tl_range = all->map->map[(all->game->element[indexor("P")].px_line + 12) / 64][(all->game->element[indexor("P")].px_column + 12) / 64];
	all->play->tr_range = all->map->map[(all->game->element[indexor("P")].px_line + 12) / 64][(all->game->element[indexor("P")].px_column + 50) / 64];
	all->play->bl_range = all->map->map[(all->game->element[indexor("P")].px_line + 50) / 64][(all->game->element[indexor("P")].px_column + 12) / 64];
	all->play->br_range = all->map->map[(all->game->element[indexor("P")].px_line + 50) / 64][(all->game->element[indexor("P")].px_column + 50) / 64];
	printf("\n\ntl: %c\ntr: %c\nbl: %c\nbr: %c\n\n\n", all->play->tl_range, all->play->tr_range, all->play->bl_range, all->play->br_range);
}

void	update_hitbox(t_all *all, int line, int column, char element)
{
	int	grid_pixel_line;
	int	grid_pixel_column;
	printf("entrou no update_hitbox-------->>>>>>>>>>\n\n");
	grid_pixel_line = line * 64;
	grid_pixel_column = column * 64;
	printf("\n\n\n\n\nUPDATE DO COLETAVEL: %c\n\n\n\n\n", all->map->map[line][column]);
	if (element == 'R' || element == 'X' || element == 'I' || element == 'T')
		check_letters_colected(all, element, line, column);
	if (((element != 'Y') && (element != 'E')))
	{
		printf("Passou do map[location] = '0'\n\n");
		all->map->map[line][column] = '0';
		printf("\n\n\n\n\nUPDATE DO COLETAVEL: %c\n\n\n\n\n", all->map->map[line][column]);
		mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, grid_pixel_column, grid_pixel_line);	
		// if (all->map->map[line][column] != 'Y')
	}
	// if (all->map->map[line][column] != 'Y')
	// {
		
	// }
	// update_player_range(all);
}


int	check_hitbox(t_all *all, char element)
{
	printf("entrou no check_hitbox----------->>>>>>>>>>>>>>>>>\n\n");
	if (all->map->map[(all->game->element[indexor("P")].px_line + 12) / 64][(all->game->element[indexor("P")].px_column + 12) / 64] == element)
	{
		update_hitbox(all, ((all->game->element[indexor("P")].px_line + 12) / 64), ((all->game->element[indexor("P")].px_column + 12) / 64), element);
		return (1);
	}
	if (all->map->map[(all->game->element[indexor("P")].px_line + 12) / 64][(all->game->element[indexor("P")].px_column + 50) / 64] == element)
	{
		update_hitbox(all, ((all->game->element[indexor("P")].px_line + 12) / 64), ((all->game->element[indexor("P")].px_column + 50) / 64), element);
		return (1);
	}
	if (all->map->map[(all->game->element[indexor("P")].px_line + 50) / 64][(all->game->element[indexor("P")].px_column + 12) / 64] == element)
	{
		update_hitbox(all, ((all->game->element[indexor("P")].px_line + 50) / 64), ((all->game->element[indexor("P")].px_column + 12) / 64), element);
		return (1);
	}
	if (all->map->map[(all->game->element[indexor("P")].px_line + 50) / 64][(all->game->element[indexor("P")].px_column + 50) / 64] == element)
	{
		update_hitbox(all, ((all->game->element[indexor("P")].px_line + 50) / 64), ((all->game->element[indexor("P")].px_column + 50) / 64), element);
		return (1);
	}
	return (0);
}

int	check_player_range(t_all *all, char element)
{
	printf("entrou no CHECK_PLAYER_RANGE 1------>>>>>>>>\n\n");
	if (all->play->tl_range != element)
	{
		printf("saiu no: tl\n");
		// update_hitbox(all, (all->game->element[indexor("P")].px_line / 64), (all->game->element[indexor("P")].px_column / 64));
		return (1);
	}
	if (all->play->tr_range != element) 
	{
		printf("saiu no: tr\n");
		// update_hitbox(all, (all->game->element[indexor("P")].px_line / 64), ((all->game->element[indexor("P")].px_column + 63) / 64));
		return (1);
	}
	if (all->play->bl_range != element)
	{
		printf("saiu no: bl\n");
		// update_hitbox(all, ((all->game->element[indexor("P")].px_line + 63) / 64), (all->game->element[indexor("P")].px_column / 64));
		return (1);
	}
	if (all->play->br_range != element) 
	{
		printf("saiu no: br\n");
		// update_hitbox(all, ((all->game->element[indexor("P")].px_line + 63) / 64), ((all->game->element[indexor("P")].px_column + 63) / 64));
		return (1);
	}
	return (0);
}
// Todos coletaveis:
void	update_game(t_all *all)
{
	if (check_player_range(all, '0') == 1)
	{
		if ((all->states->full_colectables == 0) && (check_hitbox(all, 'C') == 1))
		{
			write(1, "\a", 1);
			all->play->colected++;
			if (all->play->colected >= all->game->element[indexor("C")].count)
				all->states->full_colectables = 1;
			// all->map->map[all->play->line][all->play->column] = '0';
		}
		else if  ((all->play->R == 0) && (check_hitbox(all, 'R') == 1))
		{
			write(1, "\a", 1);
			// static int flag = 1;
			// if (flag == 1)
			// {
			// 	mlx_new_window(all->mlx, 320, 320, "TERMINAL");
			// 	flag = 0;
			// }
			// if (check_letters_colected(all) == 1)
			// 	all->states->right_letters = 1;
			// all->map->map[all->play->line][all->play->column] = '0';	
			all->play->R = 1;
		}
		else if ((all->play->X == 0) && (check_hitbox(all, 'X') == 1))
		{
			write(1, "\a", 1);
			// static int flag = 1;
			// all->states->terminal = 1;
			// if (check_letters_colected(all) == 1)
			// 	all->states->right_letters = 1;
			// all->map->map[all->play->line][all->play->column] = '0';
			all->play->X = 1;
		}
		else if ((all->play->I == 0) && (check_hitbox(all, 'I') == 1))
		{
			write(1, "\a", 1);
			// static int flag = 1;
			// if (flag == 1)
			// {
			// 	mlx_new_window(all->mlx, 320, 320, "TERMINAL");
			// 	flag = 0;
			// }
			// if (check_letters_colected(all) == 1)
			// 	all->states->right_letters = 1;
			// all->map->map[all->play->line][all->play->column] = '0';	
			all->play->I = 1;
		}
		else if ((all->play->T == 0) && (check_hitbox(all, 'T') == 1))
		{
			write(1, "\a", 1);
			// static int flag = 1;
			// if (flag == 1)
			// {
			// 	mlx_new_window(all->mlx, 320, 320, "TERMINAL");
			// 	flag = 0;
			// }
			// if (check_letters_colected(all) == 1)
			// 	all->states->right_letters = 1;
			// all->map->map[all->play->line][all->play->column] = '0';	
			all->play->T = 1;
		}
		if ((check_hitbox(all, 'Y') == 1))
		{
			if (all->states->key_enter == 1)
				all->states->terminal = 1;
			printf("Y state: 1     Terminal state: %d\n\n", all->states->terminal);
		}
		if ((check_hitbox(all, 'E') == 1) && (all->states->won == 1))
		{
			all->states->full_colectables = 0;
			mlx_clear_window(all->mlx, all->window);
			mlx_destroy_window(all->mlx, all->window);
			exit (0);
		}
	}
	printf("\nCOLECTED: %d\n", all->play->colected);
	// printf("Letter State: %d\nCoin State: %d\n\n", all->states->right_letters, all->states->full_colectables);
	printf("Todos coletaveis: %d\n\nLetras corretas: %d\n\nUndefined behavior: %d\n\n", all->states->full_colectables, all->states->right_letters, all->states->undefined_behavior);
	printf("Memory available: %d\n", all->game->memory);
	if (all->states->full_colectables == 1 && all->states->right_letters == 1 && all->states->won == 0)
	{
		all->states->won = 1;
		mlx_put_image_to_window(all->mlx, all->window, all->images->exit->mlx_st, all->game->element[indexor("E")].column * 64, all->game->element[indexor("E")].line * 64);	
	}
	// if (all->states->won == 1 && all->map->map[all->game->element[indexor("P")].column][all->game->element[indexor("P")].line] == 'E')
	// {
	// 	mlx_clear_window(all->mlx, all->window);
	// 	mlx_destroy_window(all->mlx, all->window);
	// 	exit (0);
	// }
	mlx_do_sync(all->mlx);
}

int	callback(int code, void *arg)
{
	// static int steps;
	t_all *all = (t_all *)arg;
	// static int	previous_pixel_column;
	// static int	previous_pixel_line;
	int speed = all->game->speed;

	if (all->states->undefined_behavior == 1)
		speed = -speed;
	all->play->p_pixel_column = all->game->element[indexor("P")].px_column;
	all->play->p_pixel_line = all->game->element[indexor("P")].px_line;
	(void)code;
	// if (code == 100 || code == 97 || code == 119 || code == 115)
	// 	steps++;
	// write(1, "Steps: ", 7);
	// putnumber(steps);
	// write(1, "\n", 1);
// -------------------------------
	int	yes = 63 * (speed > 0);
	int	no = 63 * (speed < 0);
	

	if (all->states->terminal != 1)
	{
	// while (code == 100)
	// {
		if ((all->states->key_d == 1) && (all->map->map[(all->game->element[indexor("P")].px_line + yes) / 64][(all->game->element[indexor("P")].px_column + yes + speed) / 64] != '1') 
			&& (all->map->map[(all->game->element[indexor("P")].px_line + no) / 64][(all->game->element[indexor("P")].px_column + yes + speed) / 64] != '1'))
			// (code == 100 && all->map->map[(all->game->element[indexor("P")].px_line + 64) / 64][(all->game->element[indexor("P")].px_column + 64 + 10 - 1) / 64] != '1'))
			all->game->element[indexor("P")].px_column += speed;
		// else if ((all->states->key_d == 1) && (all->map->map[(all->game->element[indexor("P")].px_line + yes) / 64][(all->game->element[indexor("P")].px_column + yes + speed) / 64] != '1') 
		// 	&& (all->map->map[(all->game->element[indexor("P")].px_line + no) / 64][(all->game->element[indexor("P")].px_column + yes + speed) / 64] != '1'))
		// 	all->game->element[indexor("P")].px_column += 8;
		// mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
		// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->game->element[indexor("P")].px_column, all->game->element[indexor("P")].px_line);
	// }

	// esquerda
	// while (code == 97)
	// {
		if ((all->states->key_a == 1) && (all->map->map[(all->game->element[indexor("P")].px_line + no) / 64][(all->game->element[indexor("P")].px_column + no - speed) / 64] != '1') && 
			(all->map->map[(all->game->element[indexor("P")].px_line + yes) / 64][(all->game->element[indexor("P")].px_column + no - speed) / 64] != '1'))
			// (code == 97 && all->map->map[(all->game->element[indexor("P")].px_line + 64) / 64][(all->game->element[indexor("P")].px_column - 10 - 1) / 64] != '1'))
			all->game->element[indexor("P")].px_column -= speed;
		// else if ((all->states->key_a == 1) && (all->map->map[(all->game->element[indexor("P")].px_line) / 64][(all->game->element[indexor("P")].px_column - 8) / 64] != '1') && 
		// 	(code == 97 && all->map->map[(all->game->element[indexor("P")].px_line + yes) / 64][(all->game->element[indexor("P")].px_column - 8) / 64] != '1'))
		// 	all->game->element[indexor("P")].px_column -= 8;
	// }
	// cima
	// while (code == 19)
	// {
		if ((all->states->key_w == 1) && (all->map->map[(all->game->element[indexor("P")].px_line + no - speed) / 64][(all->game->element[indexor("P")].px_column + no) / 64] != '1') &&
			(all->map->map[(all->game->element[indexor("P")].px_line + no - speed) / 64][(all->game->element[indexor("P")].px_column + yes) / 64] != '1'))
			// (code == 119 && all->map->map[(all->game->element[indexor("P")].px_line - 10 - 1 + 64) / 64][all->game->element[indexor("P")].px_column / 64] != '1'))
			all->game->element[indexor("P")].px_line -= speed;
		// else if ((all->states->key_w == 1) && (all->map->map[(all->game->element[indexor("P")].px_line - 8) / 64][all->game->element[indexor("P")].px_column / 64] != '1') &&
		// 	(all->map->map[(all->game->element[indexor("P")].px_line - 8) / 64][(all->game->element[indexor("P")].px_column + yes) / 64] != '1'))
		// 	all->game->element[indexor("P")].px_line -= 8;		
	// }
	// baixo
	// while (code == 115)
	// {
		if ((all->states->key_s == 1) && (all->map->map[(all->game->element[indexor("P")].px_line + yes + speed) / 64][(all->game->element[indexor("P")].px_column + yes) / 64] != '1') &&
				(all->map->map[(all->game->element[indexor("P")].px_line + yes + speed) / 64][(all->game->element[indexor("P")].px_column + no) / 64] != '1'))
			// (code == 115 && all->map->map[(all->game->element[indexor("P")].px_line + 64 + 80 - 1) / 64][all->game->element[indexor("P")].px_column / 64] != '1'))
			all->game->element[indexor("P")].px_line += speed;
		// else if ((all->states->key_s == 1) && (all->map->map[(all->game->element[indexor("P")].px_line + yes + 8) / 64][(all->game->element[indexor("P")].px_column + yes) / 64] != '1') &&
		// 		(all->map->map[(all->game->element[indexor("P")].px_line + 63 + 8) / 64][all->game->element[indexor("P")].px_column / 64] != '1'))
		// 	all->game->element[indexor("P")].px_line += 8;		
	}
	// }
//-----------------------------
		
	// Atualiza o INDEX do player na MATRIZ!!
	all->game->element[indexor("P")].column = all->game->element[indexor("P")].px_column / 64;
	all->game->element[indexor("P")].line = all->game->element[indexor("P")].px_line / 64;

	// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->game->element[indexor("P")].px_column, all->game->element[indexor("P")].px_line);
	// update_images(all->mlx, all->window, all, previous_pixel_column, previous_pixel_line);
	// mlx_put_image_to_window(all->mlx, all->window, all->images->grass->mlx_st, previous_pixel_column, previous_pixel_line);
	// mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->game->element[indexor("P")].px_column, all->game->element[indexor("P")].px_line);
	// mlx_do_sync(all->mlx);
	update_player_range(all);
	update_game(all);                                               
	return (0);
}

int	check_key_pressed(int	code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	printf("code %d\n", code);
	if (code == 100)
		all->states->key_d = 1;
	if (code == 97)
		all->states->key_a = 1;
	if (code == 119)
		all->states->key_w = 1;
	if (code == 115)
		all->states->key_s = 1;
	if (code == 65293)
	{
		// all->states->key_enter = 1;
		if ((check_hitbox(all, 'Y') == 1) && all->states->terminal_hook_flag == 0)
		{
			all->states->terminal_hook_flag = 1;
			all->states->terminal = 1;
			// open_terminal(all);
		}
		else
			all->states->terminal_hook_flag = 0;
	}
	if (code == 65506)
		all->states->key_shift = 1;
	// callback(code, all);
	return (0);
}

int	check_key_released(int code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	// printf("entrou no key released\n");
	if (code == 100)
		all->states->key_d = 0;
	if (code == 97)
		all->states->key_a = 0;
	if (code == 119)
		all->states->key_w = 0;
	if (code == 115)
		all->states->key_s = 0;
	if (code == 65506)
		all->states->key_shift = 0;
	// if (code == 65293)
	// 	all->states->key_enter = 0;
	// callback(code, all);
	return (0);
}

int	compare_message(char *string1, char *string2, int limit)
{
	int	index1;
	int	index2;

	index1 = 0;
	index2 = 0;
	printf("Limit: %d\n\n", limit);
	while(string2[index2] != '_' && string1[index1] && string2[index2] && 
		string1[index1] == string2[index2] && limit > 0)
	{
		printf("\ncomparason between: %c and %c\n\n", string1[index1], string2[index2]);
		index1++;
		index2++;
		limit--;
	}
	if (string2[index2] == '_' || (string2[index2] >= 48 && string2[index2] <= 57))
		index2--;
	if (index1 > 0)
		index1--;
	printf("Returning: %c (%d)  minus  %c (%d)\n\n", string1[index1], string1[index1], string2[index2], string2[index2]);
	return (string1[index1] - string2[index2]);
}

void	check_message(t_all *all)
{
	int	size;

	size = 0;
	while (all->game->writed[size] && all->game->writed[size] != '_')
		size++;
	// int	a = 10;
	// while (a-- > 0)
	// 	printf("size: %d    Compare: %d\n\n------------------------->>>>>>>>>>>>>>>>>>>>>>>>>", size, compare_message("free(string)", all->game->writed, (12 - (5 * (size == 12)))));
	
	if ((size == 12) && (compare_message("free(memory)", all->game->writed, 12) == 0))
	{
		// printf("size: %d    Compare: %d\n\n------------------------->>>>>>>>>>>>>>>>>>>>>>>>>", size, compare_message("free(string)", all->game->writed, (12 - (5 * (size == 12)))));
		all->game->memory = 0;
		all->states->undefined_behavior = 0;
		return ;
	}
	else if ((size == 9) && (compare_message("malloc(", all->game->writed, 7) == 0))
	{
		all->game->memory = (all->game->writed[7] - 48);
		return ;
	}
}

int new_window_key_released(int keycode, void *arg)
{
	t_all *all;

	all = (t_all *)arg;
	if (keycode == 65505 || keycode == 65506)
		all->states->key_shift = 0;
	if (keycode == 65507 || keycode == 65508)
		all->states->key_ctrl = 0;
	return (0);
}

void	put_shift_character(t_all *all, int	code, int line)
{
	if (code == 57)
	{
		all->game->writed[all->game->writed_index] = '(';
        all->game->writed[all->game->writed_index + 1] = '_';
        all->game->writed[all->game->writed_index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), (30 + (line * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (line * 20), 16711680, all->game->writed);
		all->game->writed_index++;
	}
	if (code == 48)
	{
        all->game->writed[all->game->writed_index] = ')';
        all->game->writed[all->game->writed_index + 1] = '_';
        all->game->writed[all->game->writed_index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 11 + ((all->game->writed_index) * 6), (30 + (line * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (line * 20), 16711680, all->game->writed);
		all->game->writed_index++;
	}
}

//adaptar os códigos para diferentes tipos de teclado.... shift 8, e shift 9 são para windows PT-BR, verificar os teclados dos 2 clusters da 42.

                                  //       IMPORTANTE


void	put_string_on_terminal(t_all *all, char x, int line, int line_index)
{
	int	count;

	count = 5;
	while (count > 0)
	{
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + ((line + count) * 20), 16711680, all->game->writed);
		count--;
	}
}
								  
int new_window_key_pressed(int keycode, void *arg)
{
	t_all *all;
	static int	line = 0;

	printf("key pressed: %d\n", keycode);
	all = (t_all *)arg;
	// static int	line = 10;
	// static int	column = 30;
	if (keycode == 65505 || keycode == 65506)
		all->states->key_shift = 1;
	if (keycode == 65507 || keycode == 65508)
		all->states->key_ctrl = 1;
	if ( (all->game->writed_index < 27) && all->states->key_shift == 1 && (keycode == 57 || keycode == 48))
		put_shift_character(all, keycode, line);
    else if ((all->game->writed_index < 27) && (all->states->key_shift == 0)  && (all->states->key_ctrl == 0) && 
		((keycode >= 0 && keycode <= 25) || (keycode >= 97 && keycode <= 122) || (keycode == 32) || (keycode >= 48 && keycode <= 57)))
	{
        all->game->writed[all->game->writed_index] = (char)keycode;
        all->game->writed[all->game->writed_index + 1] = '_';
        all->game->writed[all->game->writed_index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), (30 + (line * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (line * 20), 16711680, all->game->writed);
		all->game->writed_index++;
	}
	else if (keycode == 65288)
	{
		all->game->writed[all->game->writed_index] = '\0';
		if (all->game->writed_index > 0)
			all->game->writed_index--;
		all->game->writed[all->game->writed_index] = '_';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), (30 + (line * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (line * 20), 16711680, all->game->writed);
	}
	// if (keycode == 65307)
    else if (keycode == 65293)
	{
		// if (all->states->terminal_hook_flag == 1)
		// 	all->states->terminal_hook_flag = 0;
		check_message(all);
		// all->game->writed_index--;
		// mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), (30 + (line * 20)) - 10);
		all->game->writed_index = 0;
		all->game->writed[all->game->writed_index] = '_';
		all->game->writed[all->game->writed_index + 1] = '\0';
		line++;
		printf("Line no mini-terminal %d\n", line);
		all->states->key_a = 0;
		all->states->key_d = 0;
		all->states->key_s = 0;
		all->states->key_w = 0;
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), (30 + (line * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (line * 20), 16711680, all->game->writed);
		// usleep(10000);
		// else if (all->states->terminal_hook_flag == 0)
		// {
			// }
	}
	if (all->states->key_ctrl == 1 && keycode == 99)
	{
		all->game->writed_index = 0;
		all->states->terminal = 0;
		all->states->key_enter = 0;
		all->states->key_ctrl = 0;
		all->states->key_a = 0;
		all->states->key_d = 0;
		all->states->key_s = 0;
		all->states->key_w = 0;
		line = 0;
		mlx_destroy_window(all->mlx, all->window_terminal);
		usleep(1000);
		all->window_terminal = NULL;
		all->states->terminal_hook_flag = 0;
		
	}
        printf("Tecla Enter pressionada\n"); 	
    return 0;
}

// c2r6s13% 

// int key_hook(int keycode, void *arg)
// {
// 	t_all *all;

// 	printf("key pressed: %d\n", keycode);
// 	all = (t_all *)arg;
// 	// static int	line = 10;
// 	// static int	column = 30;
//     if ((keycode >= 0 && keycode <= 25) || (keycode >= 97 && keycode <= 122) || (keycode == 32)
// 	|| (keycode >= 48 && keycode <= 57))
// 	{
//         all->game->writed[all->game->writed_index] = (char)keycode;
//         all->game->writed[all->game->writed_index + 1] = '_';
//         all->game->writed[all->game->writed_index + 2] = '\0';
// 		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), line);
// 		mlx_string_put(all->mlx, all->window_terminal, 10, 30, 16711680, all->game->writed);
// 		all->game->writed_index++;
// 	}
// 	if (keycode == 65288)
// 	{
// 		all->game->writed[all->game->writed_index] = '\0';
// 		if (all->game->writed_index > 0)
// 			all->game->writed_index--;
// 		all->game->writed[all->game->writed_index] = '_';
// 		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->game->writed_index) * 6), 21);
// 		mlx_string_put(all->mlx, all->window_terminal, 10, 30, 16711680, all->game->writed);
// 	}
// 	// if (keycode == 65307)
// 	if (keycode == 65293)
// 	{
// 		if (all->states->terminal_hook_flag == 1)
// 			all->states->terminal_hook_flag = 0;
// 		else if (all->states->terminal_hook_flag == 0)
// 		{
// 			check_message(all);
// 			all->game->writed_index = 0;
// 			all->game->writed[all->game->writed_index] = '\0';
// 			all->states->terminal = 0;
// 			all->states->key_enter = 0;
// 			all->states->key_a = 0;
// 			all->states->key_d = 0;
// 			all->states->key_s = 0;
// 			all->states->key_w = 0;
// 			mlx_destroy_window(all->mlx, all->window_terminal);
// 			usleep(1000);
// 			all->window_terminal = NULL;
// 			// all->states->terminal_hook_flag = 0;
// 			// usleep(10000);
// 		}
// 	}
//         printf("Tecla Enter pressionada\n"); 	
//     return 0;
// }

void open_terminal(t_all *all)
{
	// void	*window2;

    if (!all->window_terminal)
    {
		// all->window2 = mlx_new_window(all->mlx, 160, 160, "TERMINAL");
		// usleep(100000);
		all->window_terminal = mlx_new_window(all->mlx, 180, 140, "TERMINAL");
		// mlx_key_hook(all->window_terminal, key_hook, all);
		mlx_hook(all->window_terminal, 2, 1L<<0, new_window_key_pressed, all);
		mlx_hook(all->window_terminal, 3, 1L<<1, new_window_key_released, all);
		// if (all->states->terminal_hook_flag == 1)
		// {
		// 	all->states->terminal_hook_flag = 0;
		// }
        // mlx_hook(all->window_terminal, 2, 1L<<0, key_hook, all);
        mlx_string_put(all->mlx, all->window_terminal, 10, 10, 16711680, "Comand:\n");
    }
}

int game_loop(void *arg)
{
    t_all *all = (t_all *)arg;

    if (all->states->terminal == 1)
    {
        open_terminal(all);
        // all->states->terminal = 0;
    }
	// if ((all->states->terminal != 0) && (all->window2 != NULL))
	// {
	// 	usleep(100000);
	// 	mlx_destroy_window(all->mlx, all->window2);
	// 	all->window2 = NULL;
	// }
    if (all->states->won == 1)
	{
        make_sound(900000);
		
	}
	
	// make_sound(200000);

    // Criação da janela de terminal apenas quando necessário
    // if (all->states->terminal == 1 && all->window_terminal == NULL)
    // {
    //     all->window_terminal = mlx_new_window(all->mlx, 320, 320, "TERMINAL");
    //     mlx_hook(all->window_terminal, 2, 1L<<0, key_hook, all); // key press
    //     all->states->terminal = 0;
    // }

    if ((all->states->key_a != 0 || all->states->key_w != 0 || 
         all->states->key_s != 0 || all->states->key_d != 0) && all->states->terminal == 0)
    {
        callback(1, all);
        update_background(all->images->letters_sheet, all->images->player, all->images->grass, 1, 6, all->game);
        if (all->game->shadow == 1)
            mlx_put_image_to_window(all->mlx, all->window, all->images->exit->mlx_st, all->play->p_pixel_column, all->play->p_pixel_line);
        mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->game->element[indexor("P")].px_column, all->game->element[indexor("P")].px_line);
        mlx_do_sync(all->mlx);
        usleep(all->game->usleep);
    }

    return 0;
}

void game_initializer(t_mapinfo *s_map, t_all *all)
{
    t_all_images *images;

    all->mlx = mlx_init();
    if (!all->mlx)
        exit(1);

    images = all_images_initiator(all->mlx);
    all->images = images;
    all->window = mlx_new_window(all->mlx, s_map->line_len * 64, s_map->total_lines * 64, s_map->map_name);
    if (!all->window)
        exit(1);

    all->window_terminal = NULL; // Inicializa como NULL
    general_settings(all);
    put_images(all->mlx, s_map, all->window, images);

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

int	indexor(char *x)
{
	static int	flag = 1;
	int	index;
	static char *string = 0;

	if (flag == 1)
	{
		string = x;
		flag = 0;
	}
	index = 0;
	while (string[index] != *x && (string[index]))
		index++;
	return (index);
}

void	general_settings(t_all *all)
{
	int	count;
	int	flag = 1;

	count = 0;
	all->game->speed = 2;
	all->game->usleep = 20000;
	all->game->shadow = 0;
	all->game->real_elements = "PEC10RXITYO";
	if (all->images)
		all->images->background = all->images->grass;
	if (flag == 1)
	{
		while (all->game->real_elements[count])
			count++;
		all->game->elements_quantity = count;
		indexor(all->game->real_elements);
		flag = 0;
	}
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
	*s_play = (t_playerinfo){0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, '\0', '\0', '\0', '\0', 0, 0, 0, 0};
	*s_game = (t_gameinfo){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, {{0}}};
	*states = (t_states){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	all->map = s_map;
	all->play = s_play;
	all->game = s_game;
	all->states = states;
	all->window2 = NULL;
	general_settings(all);
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
	so_long(s_map);
	printf("\nPassou aqui\n");
	if (!check_rectangle(s_map))
		return (1);
	if (!check_close_walls(s_map))
		return (1);
	if (!(check_elements(s_map, s_play, s_game)))
		return (1);
	// get_element_positions(s_game, s_map);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[0].charr, all->game->element[0].line, all->game->element[0].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[1].charr, all->game->element[1].line, all->game->element[1].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[2].charr, all->game->element[2].line, all->game->element[2].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[3].charr, all->game->element[3].line, all->game->element[3].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[4].charr, all->game->element[4].line, all->game->element[4].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[5].charr, all->game->element[5].line, all->game->element[5].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[6].charr, all->game->element[6].line, all->game->element[6].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[7].charr, all->game->element[7].line, all->game->element[7].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[8].charr, all->game->element[8].line, all->game->element[8].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[9].charr, all->game->element[9].line, all->game->element[9].column);
	printf("1 element: %c  line: %d  column:  %d\n\n", all->game->element[10].charr, all->game->element[10].line, all->game->element[10].column);
	// printf("EU AQUI------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	if (!check_all_paths(s_map, s_play, s_game))
		return (1);
	write(1, "teste123", 5);
	if (!check_map_size(all))
		return (1);
	game_initializer(s_map, all);
	free(s_map);
}
//e_linefree_m

// COMANDO PRA PEGAR O USER DA PESSOA e colocar num novo arquivo local
// name=$(cd /home && ls -l | awk '{print $3}' | tail -1) && echo $name >> ./user_name.txt

// COMANDO PRA PEGAR O COMPUTADOR DA PESSOA e colocar num novo arquivo local
//echo $HOST | cut -d'.' -f1 > ./computer_number.txt

// compilar com
// cc -Wall -Wextra -Werror -I libft -I MiniLibX/minilibx-linux so_long.c libft/parcing.c libft/utils.c libft/getnextline.c -L MiniLibX/minilibx-linux -lmlx -lXext -lX11 -lm