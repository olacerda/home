/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/06 20:03:06 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int		check_map_adrees_need(char *map_name)
{
	int		index;
	int		mp_size;
	char	*comparison;
	mp_size = 0;
	while (map_name[mp_size])
		mp_size++;
	if (mp_size < 10)
		return (1);
	comparison = "maps/";
	index = 0;
	while (index < 5)
	{
		if (comparison[index] != map_name[index])
			return (1);
		index++;
	}
	if (comparison[index] == '\0')
		return (0);
	return (1);
}

char	*get_map_adress(char *map_name)
{
	char	*adress;
	char	*addition;
	int		adr_idx;
	int		index;
	int		name_length;

	if (check_map_adrees_need(map_name) == 0)
		return (map_name);
	if (!map_name)
		return (NULL);
	name_length = strlength(map_name);
	adress = malloc((name_length + 5 + 1) * sizeof(char));
	if (!adress)
		return (NULL);
	addition = "maps/";
	index = -1;
	adr_idx = 0;
	while (addition[++index] && (adr_idx < name_length + 5 + 1))
		adress[adr_idx++] = addition[index];
	index = -1;
	while ((map_name[++index] != '\0') && (adr_idx < name_length + 5 + 1))
		adress[adr_idx++] = map_name[index];
	adress[adr_idx] = '\0';
	return (adress);
}

char **create_map(t_mapinfo *map)
{
	char	**matriz;
	int		line;
	int		fd;

	fd = open(map->map_adress, O_RDONLY);
	if (fd < 0)
		return (NULL);
	matriz = malloc ((map->total_lines + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	line = -1;
	while(++line < map->total_lines)
		matriz[line] = getnextline(fd);
	matriz[line] = NULL;
	return (close(fd), matriz);
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

t_sheet *sheet_initiator(void *mlx, int	sprite_number)
{
	t_sheet	*sheet;

	sheet = malloc(sizeof(t_sheet));
	if (!sheet)
		return (NULL);
	if (sprite_number == 1)
		sheet->st = mlx_xpm_file_to_image(mlx, 
			"textures/wg.xpm", &sheet->wide, &sheet->tall);
	if (sprite_number == 2)
		sheet->st = mlx_xpm_file_to_image(mlx, 
			"textures/let.xpm", &sheet->wide, &sheet->tall);
	if (sprite_number == 3)
		sheet->st = mlx_xpm_file_to_image(mlx,
			"textures/terminal_art_1.xpm", &sheet->wide, &sheet->tall);
	if (sprite_number == 4)
		sheet->st = mlx_xpm_file_to_image(mlx, 
			"textures/red_letters.xpm", &sheet->wide, &sheet->tall);
	sheet->img = mlx_get_data_addr(sheet->st, &sheet->bpp, 
		&sheet->sizeline, &sheet->endian);				
	return (sheet);
}



t_image	*image_initiator(void *mlx, int size, char charr, t_element *elements)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->tall = TALL * size;
	image->wide = WIDE * size;
	image->mlx_st = mlx_new_image(mlx, image->wide, image->tall);
	if (charr != '\0')
		elements[indexor(&charr)].mlx = image->mlx_st;
	if (!image->mlx_st)
		return (NULL);
	image->img = mlx_get_data_addr(image->mlx_st, &image->bpp, 
		&image->sizeline, &image->endian);
	if (charr != '\0')
		elements[indexor(&charr)].img = image->img;
	if (!image->img)
		return (NULL);
	return (image);
}

void	sheet_to_image2(t_sheet *src, t_image *dst, t_image *background, int nbr)
{
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	int	ints_per_line;

	ints_per_line = ((src->bpp * dst->wide) / 32);
	src_idx = ((dst->sizeline / 4) * (nbr % (src->wide / dst->wide))) + 
		((src->sizeline / 4) * ((nbr / (src->wide / dst->wide)) * dst->tall));
	img_line = -1;
	dst_idx = 0;
	while (++img_line < dst->tall)
	{
		count = -1;
		while((++count < ints_per_line))
		{
			if (((int *)src->img)[src_idx] == 16777215)
				((int *)dst->img)[dst_idx] = ((int *)background->img)[dst_idx];
			else
				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
			dst_idx++;
			src_idx++;		
		}
		src_idx = src_idx + ((src->sizeline / 4) - (count));
	}
}

void	sheet_to_image(t_sheet *src, t_image *dst, t_image *background, int nbr)
{
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	int	ints_per_line;

	ints_per_line = ((src->bpp * dst->wide) / 32);
	src_idx = ((dst->sizeline / 4) * (nbr % (src->wide / dst->wide))) + 
		((src->sizeline / 4) * ((nbr / (src->wide / dst->wide)) * dst->tall));
	img_line = -1;
	dst_idx = 0;
	while (++img_line < dst->tall)
	{
		count = -1;
		while((++count < ints_per_line))
		{
			if (((int *)src->img)[src_idx] == -16777216 || ((int *)src->img)[src_idx] == 16777215)
				((int *)dst->img)[dst_idx] = ((int *)background->img)[dst_idx];
			else
				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
			dst_idx++;
			src_idx++;		
		}
		src_idx = src_idx + ((src->sizeline / 4) - (count));
	}
}

t_background	*calculate_vars(t_all *all, t_sheet *src, t_image *dst, int nbr)
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

void	update_bg(t_sheet *src, t_image *bg, t_all *all, int nbr)
{
	static t_background *x;

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
			if (((int *)src->img)[x->src_idx] == -16777216)
				((int *)x->play)[x->dst_idx] = ((int *)bg->img)[x->bg_idx];
			else
				((int *)x->play)[x->dst_idx] = ((int *)src->img)[x->src_idx];
			x->dst_idx++;
			x->src_idx++;
		}
		x->img_line++;
		x->src_idx = x->src_idx + ((src->sizeline / 4) - x->count);
	}
	free(x);
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

void	all_sheets_initiator(void *mlx, t_all_images *images)
{
	images->grass_wall_sheet = sheet_initiator(mlx, 1);
	images->letters_sheet = sheet_initiator(mlx, 2);
	images->terminal_sheet = sheet_initiator(mlx, 3);
	images->red_letters_sheet = sheet_initiator(mlx, 4);
}

t_all_images	*all_images_initiator(void *mlx, t_all *all)
{
	t_all_images *images;

	images = malloc(sizeof(t_all_images));
	if (!images)
		return (NULL);
	all_sheets_initiator(mlx, images);
	images->R = image_initiator(mlx, 1, 'R', all->game->element);
	images->X = image_initiator(mlx, 1, 'X', all->game->element);
	images->I = image_initiator(mlx, 1, 'I', all->game->element);
	images->T = image_initiator(mlx, 1, 'T', all->game->element);
	images->Y = image_initiator(mlx, 1, 'Y', all->game->element);
	images->grass = image_initiator(mlx, 1, '0', all->game->element);
	images->wall = image_initiator(mlx, 1, '1', all->game->element);
	images->collectable = image_initiator(mlx, 1,'C', all->game->element);
	images->exit = image_initiator(mlx, 1, 'E', all->game->element);
	images->color = image_initiator(mlx, 10,'\0', all->game->element);
	images->blank_letter = image_initiator(mlx, 10, '\0', all->game->element);
	images->player = image_initiator(mlx, 1, 'P', all->game->element);
	images->background = image_initiator(mlx, 1, '\0', all->game->element);
	images->number1 = image_initiator(mlx, 1, '\0', all->game->element);
	images->number2 = image_initiator(mlx, 1, '\0', all->game->element);
	all_images_fill_buffers(images);
	return (images);
}

void	all_images_fill_buffers(t_all_images *images)
{
	sheet_to_image(images->grass_wall_sheet, images->wall, NULL, 0);
	sheet_to_image(images->grass_wall_sheet, images->grass, NULL, 1);
	sheet_to_image(images->grass_wall_sheet, images->background, NULL, 1);
	sheet_to_image(images->letters_sheet, images->player, images->grass, 25);
	color_image(images->collectable, 501000);
	color_image(images->exit, 0);
	color_image(images->color, 0);
	color_image(images->blank_letter, 0);
	sheet_to_image(images->letters_sheet, images->R, images->grass, 14);
	sheet_to_image(images->letters_sheet, images->X, images->grass, 33);
	sheet_to_image(images->letters_sheet, images->I, images->grass, 18);
	sheet_to_image(images->letters_sheet, images->T, images->grass, 29);
	sheet_to_image(images->terminal_sheet, images->Y, images->grass, 0);
}

void	put_images(t_all *all, t_mapinfo *map, t_element *ele)
{
	int	ln;
	int	column;
	int	index;

	ln = -1; 	
	while(map->map[++ln] != NULL && (ln < map->total_lines))
	{
		column = -1;
		while(map->map[ln][++column] != '\n' && (column < map->line_len))
		{
			index = 0;
			while (map->map[ln][column] != ele[index++].charr && index < all->game->elements_quantity)
				mlx_put_image_to_window(all->mlx, all->window, ele[index].mlx,
					column * 64, ln * 64);
			if ((map->map[ln][column] == 'R' || map->map[ln][column] == 'X' ||
				map->map[ln][column] == 'I' || map->map[ln][column] == 'T' ||
				map->map[ln][column] == 'E'|| map->map[ln][column] == 'P') ||
				 (map->map[ln][column] == 'Y' && all->states->bonus == 0)) 
			{
				all->map->map[ln][column] = '0';
				mlx_put_image_to_window(all->mlx, all->window, 
					all->game->element[indexor("0")].mlx, column * 64, ln * 64);
			}
		}
	}
}

void	rebuild_current_map(t_all *all)
{
	int		line;
	int		index;
	char 	**map;

	line = 0;
	index = 0;
	map = all->map->map;
	while (map[line] != NULL)
	{
		index = 0;
		while ((map[line][index] != '\n') && (map[line][index] != '\0'))
		{
			if (map[line][index] != 'P')
			{
				mlx_put_image_to_window(all->mlx, all->window, 
					all->game->element[indexor(&(map[line][index]))].mlx, 
						index * 64, line * 64);
			}
			index++;
		}
		line++;
	}
}
void	put_letter(t_all *all, char *letters)
{
	void 	*img_mlx;
	int		index;
	int		line;
	int		column;
	char	element;

	index = 0;
	while (letters[index])
	{
		line = all->game->element[indexor(&(letters[index]))].line;
		column = all->game->element[indexor(&(letters[index]))].column;
		element = all->game->element[indexor(&(letters[index]))].charr;
		all->map->map[line][column] = element;
		img_mlx = all->game->element[indexor(&(letters[index]))].mlx;
		column = column * WIDE;
		line = line * TALL;
		mlx_put_image_to_window(all->mlx, all->window, img_mlx, column, line);
		index++;
	}
}


void	update_images(t_all *all, int p_col, int p_line)
{
	int		col;
	int		line;
	void	*bg_mlx;
	void	*play_mlx;

	play_mlx = all->images->player->mlx_st;
	bg_mlx = all->images->background->mlx_st;
	col = all->game->element[indexor("P")].px_column;
	line = all->game->element[indexor("P")].px_line;
	if (all->game->shadow == 1)
		mlx_put_image_to_window(all->mlx, all->window, bg_mlx, p_col , p_line);
	mlx_put_image_to_window(all->mlx, all->window, play_mlx, col, line);
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
    static long bell_last = 0;
    long time = get_full_time();

    if (bell_last == 0) 
    {
        bell_last = time;
        write(1, "\a", 1);
        return;
    }

    if (time - bell_last > frequency)
    {
        write(1, "\a", 1);
        bell_last = time;
    }
}

void	check_letters_colected(t_all *all, char	element, int line, int column)
{
	int			index;
	char *letters;

	letters = "RXIT";
	index = -1;
	if (element == 'R' || element == 'X' || element == 'I' || element == 'T')
	{
		all->play->letter_colected[all->play->letters_colected_amount] = 
			all->map->map[line][column];
		all->play->letters_colected_amount++;
		if (all->states->undefined_behavior == 1)
		{
			// all->game->ub_current_time -= 10;
			display_ub_count(all->images, all->game, all);
		}
		if (all->play->letters_colected_amount > all->game->memory)
			all->states->undefined_behavior = 1;
		while (++index < all->play->letters_colected_amount)
		{
			if ((letters[index] != all->play->letter_colected[index]))
				return ;
		}
	}
	if (all->play->letters_colected_amount == 4)
		all->states->right_letters = 1;	
}

int	update_hitbox(t_all *all, int line, int column, char elment)
{
	int		px_line;
	int		px_col;
	void	*grass_mlx;

	grass_mlx = all->images->grass->mlx_st;
	px_line = line * 64;
	px_col = column * 64;
	if (all->map->map[line][column] == elment)
	{
		if (all->states->undefined_behavior != 1 && elment != 'Y')
			write(1, "\a", 1);
		if (elment == 'R' || elment == 'X' || elment == 'I' || elment == 'T')
			check_letters_colected(all, elment, line, column);
		if (((elment != 'Y') && (elment != 'E')))
		{
			all->map->map[line][column] = '0';
			mlx_put_image_to_window(all->mlx, all->window, grass_mlx, px_col, 
				px_line);
		}
		return (1);
	}
	return (0);
}


int	check_hitbox(t_all *all, char element)
{
	int	line;
	int	column;
	line = all->game->element[indexor("P")].px_line;
	column =  all->game->element[indexor("P")].px_column;
	if (update_hitbox(all, ((line + 12) / 64), ((column + 12) / 64), element))
		return (1);
	if (update_hitbox(all, ((line + 12) / 64), ((column + 50) / 64), element))
		return (1);
	if (update_hitbox(all, ((line + 50) / 64), ((column + 12) / 64), element))
		return (1);
	if (update_hitbox(all, ((line + 50) / 64), ((column + 50) / 64), element))
		return (1);
	return (0);
}

void	update_player_range(t_all *all, int line, int column)
{
	char	**map;
	int		lin;
	int 	col;
	void	*element_buff;

	map = all->map->map;
	element_buff = all->game->element[indexor(&(map[line][column]))].mlx;
	lin = line * WIDE;
	col = column * TALL;
	if (all->map->map[line][column] != '1')
		mlx_put_image_to_window(all->mlx, all->window, element_buff, col, lin);
}

int	check_player_range(t_all *all, char element)
{
	int	line;
	int	column;

	line = all->game->element[indexor("P")].px_line;
	column = all->game->element[indexor("P")].px_column;
	if (all->map->map[(line - 16) / 64][(column - 16) / 64] != element)
		update_player_range(all, ((line - 16) / 64), ((column - 16) / 64));
	if (all->map->map[(line - 16) / 64][(column + 79) / 64] != element)
		update_player_range(all, ((line - 16) / 64), ((column + 79) / 64));
	if (all->map->map[(line + 79) / 64][(column - 16) / 64] != element)
		update_player_range(all, ((line + 79) / 64), ((column - 16) / 64));
	if (all->map->map[(line + 79) / 64][(column + 79) / 64] != element)
		update_player_range(all, ((line + 79) / 64), ((column + 79) / 64));
	if (all->map->map[(line - 16) / 64][(column + 32) / 64] != element)
		update_player_range(all, ((line - 16) / 64), ((column + 32) / 64));
	if (all->map->map[(line + 32) / 64][(column + 79) / 64] != element)
		update_player_range(all, ((line + 32) / 64), ((column + 79) / 64));
	if (all->map->map[(line + 79) / 64][(column + 32) / 64] != element)
		update_player_range(all, ((line + 79) / 64), ((column + 32) / 64));
	if (all->map->map[(line + 32) / 64][(column - 16) / 64] != element)
		update_player_range(all, ((line + 32) / 64), ((column - 16) / 64));	
	return (0);
}

void update_major_elements(t_all *all, int line, int column)
{
	void	*exit_mlx;

	exit_mlx = all->images->exit->mlx_st;
	if ((check_hitbox(all, 'Y') == 1))
	{
		if (all->states->key_enter == 1)
			all->states->terminal = 1;
	}
	if (all->states->full_colectables == 1 && all->states->right_letters == 1 &&
			all->states->won == 0)
	{
		all->states->won = 1;
		all->map->map[line][column] = 'E';
		mlx_put_image_to_window(all->mlx, all->window, exit_mlx, column * 64, 
			line * 64);
	}
	if ((check_hitbox(all, 'E') == 1) && (all->states->won == 1))
	{
		all->states->full_colectables = 0;
		end_game(all);
	}
}

void	update_game(t_all *all)
{
	if ((all->states->full_colectables == 0) && (check_hitbox(all, 'C') == 1))
	{
		all->play->colected++;
		if (all->play->colected >= all->game->element[indexor("C")].count)
			all->states->full_colectables = 1;
	}
	else if  ((all->play->R == 0) && (check_hitbox(all, 'R') == 1))
		all->play->R = 1;
	else if ((all->play->X == 0) && (check_hitbox(all, 'X') == 1))
		all->play->X = 1;
	else if ((all->play->I == 0) && (check_hitbox(all, 'I') == 1))
		all->play->I = 1;
	else if ((all->play->T == 0) && (check_hitbox(all, 'T') == 1))
		all->play->T = 1;
	update_major_elements(all, all->game->element[indexor("E")].line, 
		all->game->element[indexor("E")].column);
	mlx_do_sync(all->mlx);
}

void	redefine_behavior_directions(t_all *all, long *time, long *last)
{
		static int flag = 0;

		if (*time - *last > 2500000)
		{
			all->game->usleep = 65000;
			(all->game->speed < 0) && (all->game->speed = -16);
			(all->game->speed > 0) && (all->game->speed = 16);
			if (flag == 0)
			{
				(all->game->speed2) = -(all->game->speed2);
				flag = 1;
			}
			// sheet_to_image(all->images->letters_sheet, all->images->background, 
			// 	all->images->grass, 25);
			all->images->background->img = all->images->grass->img;
		}
		if (*time - *last > 3500000 && flag == 1)
		{
			(all->game->speed2) = -(all->game->speed2);
			flag = 2;
		}
		if (*time - *last > 5500000)
		{
			(all->game->speed2) = -(all->game->speed2);
			(all->game->speed) = -(all->game->speed);
			*last = *time;
			flag = 0;
		}
}

void	redefine_behavior(t_all *all)
{
		static long time = 0;
		static long last = 0;

		time = get_full_time();
		if (all->game->speed == 2)
		{
			// all->game->shadow = 1;
			all->images->background->img = all->game->element[indexor(&(all->play->letter_colected[all->play->letters_colected_amount - 1]))].img;
			all->game->usleep = 65000;
			(all->game->speed) = 16;
			last = time;
		}
		if (time - last > 2000000)
		{
			all->game->usleep = 20000;
			(all->game->speed < 0) && (all->game->speed = -40);
			(all->game->speed > 0) && (all->game->speed = 40);
			// color_image(all->images->background, 0);
			all->images->background->img = all->images->color->img;
		}
		redefine_behavior_directions(all, &time, &last);
}

void	move_up(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + no - speed) / 64][(col + no) / 64] != '1') && 
		(map[(line + no - speed) / 64][(col + yes) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_line -= speed;
	}
	else if ((map[(line + no - speed2) / 64][(col + no) /64] != '1') &&
		 (map[(line + no - speed2) / 64][(col + yes) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_line -= speed2;
	}
}
void	move_left(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + no) / 64][(col + no - speed) / 64] != '1') && 
		(map[(line + yes) / 64][(col + no - speed) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_column -= speed;
	}
	else if ((map[(line + no) / 64][(col + no - speed2) / 64] != '1') &&
		 (map[(line + yes) / 64][(col + no - speed2) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_column -= speed2;
	}
}
void	move_down(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + yes + speed) / 64][(col + yes) / 64] != '1') && 
		(map[(line + yes + speed) / 64][(col + no) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_line += speed;
	}
	else if ((map[(line + yes + speed2) / 64][(col + yes) / 64] != '1') &&
		 (map[(line + yes + speed2) / 64][(col + no) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_line += speed2;
	}
}
void	move_right(t_all *all, int yes, int no)
{
	char **map;
	int	speed;
	int	speed2;
	int	line;
	int	col;

	line = all->play->p_pixel_line;
	col = all->play->p_pixel_column;
	speed = all->game->speed;
	speed2 = all->game->speed2;
	map = all->map->map;
	if ((map[(line + yes) / 64][(col + yes + speed) / 64] != '1') &&
		 (map[(line + no) / 64][(col + yes + speed) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_column += speed;
	}
	else if ((map[(line + yes) / 64][(col + yes + speed2) / 64] != '1') &&
		(map[(line + no) / 64][(col + yes + speed2) / 64] != '1'))
	{
		all->game->element[indexor("P")].px_column += speed2;
	}
}

void	move_player(t_all *all)
{
	int	yes;
	int	no;

	all->play->p_pixel_column = all->game->element[indexor("P")].px_column;
	all->play->p_pixel_line = all->game->element[indexor("P")].px_line;
	if (all->states->undefined_behavior == 1)
		redefine_behavior(all);
	yes = 63 * (all->game->speed > 0);
	no = 63 * (all->game->speed < 0);
	if (all->states->key_w == 1)
		move_up(all, yes, no);
	if (all->states->key_s == 1)
		move_down(all, yes, no);
	if (all->states->key_a == 1)
		move_left(all, yes, no);
	if (all->states->key_d == 1)
		move_right(all, yes, no);
	all->game->element[indexor("P")].column = 
		all->game->element[indexor("P")].px_column / 64;
	all->game->element[indexor("P")].line = 
		all->game->element[indexor("P")].px_line / 64;
}

int	check_key_pressed(int	code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
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
		if ((check_hitbox(all, 'Y') == 1) && all->states->terminal == 0)
			all->states->terminal = 1;
	}
	if (code == 65506)
		all->states->key_shift = 1;
	return (0);
}

int	check_key_released(int code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
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
	return (0);
}

int	cmp_msg(t_all * all, char *string1, char *string2, int limit)
{
	int	index1;
	int	index2;

	index1 = 0;
	index2 = all->terminal->pc_nb_size;
	while(string2[index2] != '_' && string1[index1] && string2[index2] && 
		string1[index1] == string2[index2] && limit > 0)
	{
		index1++;
		index2++;
		limit--;
	}
	if (string2[index2] == '_' || (string2[index2] == '\0') || 
		(string2[index2] >= 48 && string2[index2] <= 57))
		{
			index2--;
		}
	if (index1 > 0)
		index1--;
	return (string1[index1] - string2[index2]);
}

void	itoa_adder(t_all *all, char (*original)[28], int *org_idx, int to_add)
{
	printf("string antes: %s\n", original[all->terminal->wr_line]);
	if (to_add > 9)
	{
		itoa_adder(all, original, org_idx, to_add / 10);
	}
	original[all->terminal->wr_line][(*org_idx)++] = ((to_add % 10) + 48);
	printf("string depois: %s\n", original[all->terminal->wr_line]);
}

void	mesage_cat_letters(t_all *all, int *line, char (*writed)[28], char *letters)
{
	int	let_idx;
	int str_idx;
	int	wr_idx;
	char *string;

	string = "mlx_put_image(\"1\", 2, 3)";
	wr_idx = 0;
	let_idx = -1;
	writed[*line][all->terminal->wr_index] = '\0';
	(*line)++;
	while (letters[++let_idx])
	{
		wr_idx = 0;
		str_idx = -1;
		while (string[++str_idx])
		{
			writed[*line][wr_idx] = string[str_idx];
			if (writed[*line][wr_idx] == '1')
			{
				writed[*line][wr_idx] = (all->game->element[indexor(&(letters[let_idx]))].charr);
				if (writed[*line][wr_idx] == 'R')
					writed[*line][wr_idx] = 'E';
				wr_idx++;
			}
			else if (writed[*line][wr_idx] == '2')
				itoa_adder(all, writed, &wr_idx, all->game->element[indexor(&(letters[let_idx]))].column);
			else if (writed[*line][wr_idx] == '3')
				itoa_adder(all, writed, &wr_idx, all->game->element[indexor(&(letters[let_idx]))].line);
			else
				wr_idx++;
		}
		writed[*line][wr_idx] = '\0';
		if (letters[let_idx + 1])
			(*line)++;
	}
	put_strings_on_terminal(all, *line, all->images->blank_letter->mlx_st);
}

void	message_ls(t_all *all, int *line, char (*writed)[28])
{
	char	*to_write;
	int		index;

	to_write = NULL;
 	if (cmp_msg(all, "ls", writed[*line], 2) == 0)
	{
		writed[*line][all->terminal->wr_index] = '\0';
		(*line)++;
		index = 0;
		if (all->states->letters_compiled == 0)
			to_write = "   letters.c";
		else
			to_write = "   letters.c     a.out";
		while (to_write[index])
		{
			writed[*line][index] = to_write[index];
			index++;
		}
		writed[*line][index] = '\0';
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 
			16711680, writed[*line]);
	}
}

void	message_free(t_all *all, int line, char (*writed)[28])
{
	if (cmp_msg(all, "free(memory)", writed[line], 12) == 0)
	{
		rebuild_current_map(all);
		all->play->letters_colected_amount = 0;
		all->play->letter_colected[0] = '\0';
		all->game->memory = 0;
		all->game->shadow = 0;
		all->game->usleep = 20000;
		all->game->speed = 2;
		all->game->speed2 = 1;
		all->states->undefined_behavior = 0;
		all->play->R = 0;
		all->play->X = 0;
		all->play->I = 0;
		all->play->T = 0;
		all->game->ub_current_time = all->game->ub_time + 1;
		sheet_to_image(all->images->terminal_sheet, all->images->Y, all->images->grass, 0);
		all->images->background->img = all->images->grass->img;
		update_bg(all->images->letters_sheet, all->images->background, all, 25);
		mlx_put_image_to_window(all->mlx, all->window, all->images->Y->mlx_st, all->game->element[indexor("Y")].px_column, all->game->element[indexor("Y")].px_line);
		mlx_do_sync(all->mlx);
	}
}

int	message_size(t_all *all, char *string)
{
	int index;
	int size;

	size = 0;
	index = (all->terminal->pc_nb_size);
	while (string[index] && string[index] != '_')
	{
		index++;
		size++;
	}
	printf("size: %d\n", size);
	return (size);
}

void	check_message(t_all *all, int line)
{
	static int	size = 0;
	char (*writed)[28];

	writed = all->terminal->writed;
	size = message_size(all, writed[line]);
	if (size == 2)
		message_ls(all, &all->terminal->wr_line, writed);
	else if ((size == 7) && (all->states->letters_compiled == 1) && 
		(cmp_msg(all, "./a.out", writed[line], 7) == 0))
	{
		put_letter(all, "RXIT");
	}
	else if ((size == 9) && (cmp_msg(all, "malloc(", writed[line], 8) == 0))
		all->game->memory = (writed[line][all->terminal->pc_nb_size + 7] - 48);
	else if (size == 12)
		message_free(all, line, writed);
	else if (size == 13 || size == 10 || size == 9)
		mesage_cat_letters(all, &all->terminal->wr_line, writed, "RXIT");
	 if ((size == 12) && 
				(cmp_msg(all, "cc letters.c", writed[line], 12)) == 0)
		all->states->letters_compiled = 1;
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

void	key_shift_character(t_all *all, int	code, int line, int *index)
{
	if (all->terminal->wr_index < 27 && all->states->key_shift == 1)
	{
		if (code == 57)
		{
			all->terminal->writed[line][*index] = '(';
			all->terminal->writed[line][*index + 1] = '_';
			all->terminal->writed[line][*index + 2] = '\0';
			mlx_put_image_to_window(all->mlx, all->window_terminal, 
				all->images->blank_letter->mlx_st, 10 + ((*index) * 6), 120);
			mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 
				16711680, all->terminal->writed[line]);
			(*index)++;
		}
		if (code == 48)
		{
			all->terminal->writed[line][*index] = ')';
			all->terminal->writed[line][*index + 1] = '_';
			all->terminal->writed[line][*index + 2] = '\0';
			mlx_put_image_to_window(all->mlx, all->window_terminal, 
				all->images->blank_letter->mlx_st, 11 + ((*index) * 6), 120);
			mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 
				16711680, all->terminal->writed[line]);
			(*index)++;
		}
	}
}

void	put_strings_on_terminal(t_all *all, int line, void *blank)
{
	int	count;

	count = 0;
	mlx_put_image_to_window(all->mlx, all->window_terminal, blank, 0, 10);
	while (count < 5)
	{
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (count * 20),
			16711680, all->terminal->writed[line - 4 + count]);
		count++;
	}
}

void	save_current_string(t_all *all, int keycode, int line)
{
	char (*writed)[28];
	int *line_size;

	writed = all->terminal->writed;
	line_size = &all->terminal->current_line_size;
	if (all->states->swifting_strings == 0 && keycode == 65362 && 
		all->terminal->string_focused > 5)
	{
		while ((writed[line][*line_size] != '_') && writed[line][*line_size])
		{
			writed[line + 1][*line_size] = writed[line][*line_size];
			(*line_size)++;
		}
		all->states->swifting_strings = 1;
	}
}

void	put_string_focused(t_all *all, int line, int focused)
{
	char	(*writed)[28];
	int	index;

	writed = all->terminal->writed;
	index = 0;
	while (writed[focused][index] && (index < 27))
	{
		writed[line][index] = writed[focused][index];
		index++;
	}
	if (index > all->terminal->pc_nb_size)
	{
		writed[line][index] = '\0';
		all->terminal->wr_index = index;
	}
	else
	{
		writed[line][all->terminal->pc_nb_size] = '\0';
		all->terminal->wr_index = all->terminal->pc_nb_size;
	}
	printf("resultado do switch: wr_index %d   writed line: %s\nstr focused: %s\n\n", all->terminal->wr_index, all->terminal->writed[all->terminal->wr_line], all->terminal->writed[focused]);
	mlx_put_image_to_window(all->mlx, all->window_terminal, 
		all->images->blank_letter->mlx_st, 0, 120);
	mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20),
		16711680, writed[line]);
}

void	key_switch_strings(t_all *all, int keycode, int line, int *focused)
{
	int *swift_state;

	swift_state = &all->states->swifting_strings;
	if (*swift_state == 0 && keycode == 65362 && (*focused) > 5)
		save_current_string(all, keycode, line);
	if ((keycode == 65362) && ((*focused) > 5))
	{
		printf("Key-up, focused: %d string: %s\n\n", *focused, all->terminal->writed[*focused]);			
		--((*focused));
		printf("Key-up, focused: %d string: %s\n\n", *focused, all->terminal->writed[*focused]);
		if (((*focused)) == line && ((*focused) > 5))
		{
			(*focused)--;
			printf("Key-up, focused: %d string: %s\n\n", *focused, all->terminal->writed[*focused]);
		}
		while ((all->terminal->writed[*focused][0] != 'c') && ((*focused) > 5))
		{
			(*focused)--;
			printf("Key-up, focused: %d string: %s\n\n", *focused, all->terminal->writed[*focused]);
		}
	}
	else if ((keycode == 65364) && (*focused < (line + 1)) && *swift_state == 1)
	{
		printf("keydown, focused: %d string: %s\n", *focused, all->terminal->writed[*focused]);
		(*focused)++;
		printf("keydown, focused: %d string: %s\n", *focused, all->terminal->writed[*focused]);
		if (((*focused)) == line && (*focused) < (line + 1))
		{
			(*focused)++; 
			printf("keydown, focused: %d string: %s\n", *focused, all->terminal->writed[*focused]);
		}
		while ((all->terminal->writed[*focused][0] != 'c') && *focused < line)
		{
			(*focused)++;
			printf("Key-down, focused: %d current string: %s\n", *focused, all->terminal->writed[*focused]);
		}
	}
	put_string_focused(all, line, *focused);
}
				
void	put_pcnumber_on_terminal(t_all *all, int line)
{
	char *user_pc;
	int	*index;

	user_pc = all->terminal->user_pc_number;
	index = &all->terminal->wr_index;
	*index = 0;
	while (user_pc[*index])
	{
		all->terminal->writed[line][*index] = user_pc[*index];
		(*index)++;
	}
	all->terminal->writed[line][(*index)++] = ' ';
	all->terminal->writed[line][*index] = '\0';
}

void	key_alpha_number(t_all *all, int keycode)
{
	char (*writed)[28];
	int	line;
	int *index;
	void	*img;
	void	*window;

	writed = all->terminal->writed;
	line = all->terminal->wr_line;
	index = &all->terminal->wr_index;
	img = all->images->blank_letter->mlx_st;
	window = all->window_terminal;
	if ((*index < 27) && (all->states->key_shift == 0) 
		&& (all->states->key_ctrl == 0))
	{
		writed[line][*index] = (char)keycode;
		writed[line][*index + 1] = '_';
		writed[line][*index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, window, img, 10 + (*index * 6), 120);
		mlx_string_put(all->mlx, window, 10, 130, 16711680, writed[line]);
		(*index)++;
	}
}

void	key_erase(t_all *all, int line, int *index)
{
	if (*index > all->terminal->pc_nb_size)
	{
		all->terminal->writed[line][*index] = '\0';
		if (*index > 0)
			(*index)--;
		all->terminal->writed[line][*index] = '_';
		mlx_put_image_to_window(all->mlx, all->window_terminal, 
			all->images->blank_letter->mlx_st, 10 + ((*index) * 6), 120);
		mlx_string_put(all->mlx, all->window_terminal, 10, 130, 
			16711680, all->terminal->writed[line]);
	}
}

void	key_enter(t_all *all, int *line, int *index)
{
	int	save_line;

	save_line = *line;
	all->terminal->writed[*line][*index] = '\0';
	check_message(all, *line);
	if (*line != save_line)
		all->terminal->writed[*line][*index] = '\0';
	all->terminal->writed[*line + 1][*index] = '\0';
	put_strings_on_terminal(all, *line, all->images->blank_letter->mlx_st);
	(*line)++;
	if (*line >= 499)
		*line = 5;
	all->terminal->string_focused = *line;
	all->terminal->current_line_size = 0;
	*index = 0;
	all->states->swifting_strings = 0;
	if (*index == 0)
	{
		put_pcnumber_on_terminal(all, *line);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 
			16711680, all->terminal->writed[*line]);
	}
}

void	key_ctrl_c(t_all *all)
{
	all->terminal->wr_index = 0;
	all->states->terminal = 0;
	all->states->key_enter = 0;
	all->states->key_ctrl = 0;
	all->states->key_a = 0;
	all->states->key_d = 0;
	all->states->key_s = 0;
	all->states->key_w = 0;
	all->terminal->wr_line = 5;
	all->terminal->string_focused = all->terminal->wr_line;
	mlx_destroy_window(all->mlx, all->window_terminal);
	usleep(1000);
	all->window_terminal = NULL;
}	

int new_window_key_pressed(int keycode, void *arg)
{
	t_all *all;

	all = (t_all *)arg;
	// printf("detector de tecla-> line: %d\n\n", all->terminal->wr_line);
	if (keycode == 65505 || keycode == 65506)
		all->states->key_shift = 1;
	if (keycode == 65507 || keycode == 65508)
		all->states->key_ctrl = 1;
	if (keycode == 57 || keycode == 48)
		key_shift_character(all, keycode, all->terminal->wr_line, 
			&all->terminal->wr_index);
	else if ((keycode == 65362) || (keycode == 65364))
		key_switch_strings(all, keycode, all->terminal->wr_line, 
			&all->terminal->string_focused);
    else if ((keycode >= 0 && keycode <= 25) || keycode == 32 || (keycode == 46)
		 || (keycode == 47) || (keycode >= 97 && keycode <= 122) || 
		 	(keycode >= 48 && keycode <= 57))
		key_alpha_number(all, keycode);
	else if (keycode == 65288)
		key_erase(all, all->terminal->wr_line, &all->terminal->wr_index);
    else if (keycode == 65293)
		key_enter(all, &all->terminal->wr_line, &all->terminal->wr_index);
	if (all->states->key_ctrl == 1 && keycode == 99)
		key_ctrl_c(all);
    return 0;
}

void open_terminal(t_all *all)
{
	char *username;

	username = all->terminal->user_name;
    if (!all->window_terminal)
    {
		all->window_terminal = mlx_new_window(all->mlx, 180, 140, username);
		mlx_hook(all->window_terminal, 2, 1L<<0, new_window_key_pressed, all);
		mlx_hook(all->window_terminal, 3, 1L<<1, new_window_key_released, all);
		if (all->terminal->wr_index == 0)
		{
			put_pcnumber_on_terminal(all, all->terminal->wr_line);
			mlx_string_put(all->mlx, all->window_terminal, 10, 130, 16711680, 
				all->terminal->writed[all->terminal->wr_line]);
		}		
        mlx_string_put(all->mlx, all->window_terminal, 
			10, 10, 16711680, "Comand:\n");
    }
}

void	display_ub_count(t_all_images *images, t_gameinfo *game, t_all *all)
{
	int	center;

	center = ((all->map->line_len * WIDE) / 2);
	if (game->ub_current_time > 9 && game->ub_current_time > 5)
		sheet_to_image(images->letters_sheet, images->number1, images->wall, (game->ub_current_time / 10) - 1);
	else
		sheet_to_image(images->grass_wall_sheet, images->number1, NULL, 0);
	mlx_put_image_to_window(all->mlx, all->window, images->number1->mlx_st, center - WIDE, 0 * TALL);
	mlx_do_sync(all->mlx);
	if (game->ub_current_time <= 5)
	{
		if (game->ub_current_time >= 0)
			sheet_to_image(images->red_letters_sheet, images->number2, images->wall, ((game->ub_current_time % 10) - 1) + (10 * (((game->ub_current_time % 10)) == 0)));
		// else
		// 	sheet_to_image(images->red_letters_sheet, images->number2, images->wall, 9);
		sheet_to_image(images->red_letters_sheet, images->number1, images->wall, 39);
		mlx_put_image_to_window(all->mlx, all->window, images->number1->mlx_st, center + WIDE, 0 * TALL);
	}
	else
	{
		if (game->ub_current_time >= 0)
			sheet_to_image(images->letters_sheet, images->number2, images->wall, ((game->ub_current_time % 10) - 1) + (10 * (((game->ub_current_time % 10)) == 0)));
		else
			sheet_to_image(images->letters_sheet, images->number2, images->wall, 9);			
	}
	mlx_put_image_to_window(all->mlx, all->window, images->number2->mlx_st, center, 0 * TALL);
	mlx_do_sync(all->mlx);
}

void	display_indefined_behavior_alert(t_all *all)
{
	static int	changer = 1;

	if (changer == 2)
	{
		sheet_to_image(all->images->terminal_sheet, all->images->Y, all->images->grass, 1);
		changer = 1;
	}
	else
	{
		sheet_to_image(all->images->terminal_sheet, all->images->Y, all->images->grass, 2);
		changer = 2;
	}
	mlx_put_image_to_window(all->mlx, all->window, all->images->Y->mlx_st, all->game->element[indexor("Y")].px_column, all->game->element[indexor("Y")].px_line);
}

void	ub_count(t_all *all)
{
	static long time;
	static long last;

	time = get_full_time();
	if (all->game->ub_current_time > all->game->ub_time)
	{
		all->game->ub_current_time = all->game->ub_time;
		last = time;
		display_ub_count(all->images, all->game, all);
		display_indefined_behavior_alert(all);
	}
	if (time - last > 500000)
		display_indefined_behavior_alert(all);
	if (time - last > 1000000)
	{
		// if ()
		// all->game->ub_current_time--;
		display_ub_count(all->images, all->game, all);
		display_indefined_behavior_alert(all);
		if (all->game->ub_current_time <= 0)
		{
			usleep(200000);
			end_game(all);
		}
		last = time;
	}
}

int game_loop(void *arg)
{
    t_all *all = (t_all *)arg;

	// printf("Cor branca: %d\n\n", ((int *)all->images->Y->img)[0]);
    if (all->states->terminal == 1)
		open_terminal(all);
	if (all->states->undefined_behavior == 1)
	{
		printf("ub count: %d \n\n\n", all->game->ub_current_time);
		make_sound(200000);
		ub_count(all);
	}
    if ((all->states->key_a != 0 || all->states->key_w != 0 || 
        	all->states->key_s != 0 || all->states->key_d != 0) && 
				all->states->terminal == 0)
    {
        move_player(all);
		update_bg(all->images->letters_sheet, all->images->background, all, 25);
		check_player_range(all, '0');
    }
	update_game(all);
	update_images(all, all->play->p_pixel_column, all->play->p_pixel_line);
	mlx_do_sync(all->mlx);
	usleep(all->game->usleep);
    return 0;
}

void	get_username_and_pcnumber(t_all *all)
{
	int	fd;
	int	size;

	size = 0;
	fd = open("./maps/user_name.ber", O_RDONLY);
	all->terminal->user_name = getnextline(fd);
	if (!all->terminal->user_name)
		all->terminal->user_name = "TERMINAL";
	close(fd);
	fd = open("./maps/computer_number.ber", O_RDONLY);
	all->terminal->user_pc_number = getnextline(fd);
	all->states->pc_number = 1;
	if (!all->terminal->user_pc_number)
	{
		all->terminal->user_pc_number = "comand: ";
		all->states->pc_number = 0;
	}
	while(all->terminal->user_pc_number[size])
		size++;
	all->terminal->pc_nb_size = size + 1;
	close (fd);
}

void game_initializer(t_all *all)
{
    t_all_images *images;

    all->mlx = mlx_init();
    if (!all->mlx)
		exit(1);
	images = all_images_initiator(all->mlx, all);
	get_username_and_pcnumber(all);
    all->images = images;
    all->window = mlx_new_window(all->mlx, all->map->line_len * 
		64, all->map->total_lines * 64, all->map->map_name);
    if (!all->window)
        exit(1);
    all->window_terminal = NULL;
    general_settings(all);
    put_images(all, all->map, all->game->element);
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
	all->game->speed2 = 1;
	all->game->usleep = 20000;
	all->game->shadow = 0;
	all->game->real_elements = "PEC10RXITYO";
	all->game->ub_time = 15;
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
		write(2, "Error\nFailed structure allocation", 33);
		exit (1) ;
	}
	*map = (t_mapinfo){0, 0, 0, 0, 0};
	*play = (t_playerinfo){0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, '\0', '\0', 
		'\0', '\0', 0, 0, 0, 0};
	*game = (t_gameinfo){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	*states = (t_states){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	*terminal = (t_terminalinfo){0, 0, 5, 0, 0, 0, 5, {{0}}};
	*all = (t_all){map, play, 0, game, states, terminal, 0, 0, 0};
}

void	destroy_all_images2(void *mlx, t_all_images *images)
{
	if (images->player->mlx_st)
		mlx_destroy_image(mlx, images->player->mlx_st);
	if (images->exit->mlx_st)
		mlx_destroy_image(mlx, images->exit->mlx_st);
	if (images->color->mlx_st)
		mlx_destroy_image(mlx, images->color->mlx_st);
	if (images->blank_letter->mlx_st)
		mlx_destroy_image(mlx, images->blank_letter->mlx_st);
	if (images->background->mlx_st)
		mlx_destroy_image(mlx, images->background->mlx_st);
	if (images->number1->mlx_st)
		mlx_destroy_image(mlx, images->number1->mlx_st);
	if (images->number2->mlx_st)
		mlx_destroy_image(mlx, images->number2->mlx_st);
	if (images->terminal_sheet->st)
		mlx_destroy_image(mlx, images->terminal_sheet->st);
}

void	destroy_all_images1(void *mlx, t_all_images *images)
{
	if (images->grass_wall_sheet->st)
		mlx_destroy_image(mlx, images->grass_wall_sheet->st);
	if (images->letters_sheet->st)
		mlx_destroy_image(mlx, images->letters_sheet->st);
	if (images->red_letters_sheet->st)
		mlx_destroy_image(mlx, images->red_letters_sheet->st);		
	if (images->wall->mlx_st)
		mlx_destroy_image(mlx, images->wall->mlx_st);
	if (images->grass->mlx_st)
		mlx_destroy_image(mlx, images->grass->mlx_st);
	if (images->collectable->mlx_st)
		mlx_destroy_image(mlx, images->collectable->mlx_st);
	if (images->R->mlx_st)
		mlx_destroy_image(mlx, images->R->mlx_st);
	if (images->X->mlx_st)
		mlx_destroy_image(mlx, images->X->mlx_st);
	if (images->I->mlx_st)
		mlx_destroy_image(mlx, images->I->mlx_st);
	if (images->T->mlx_st)
		mlx_destroy_image(mlx, images->T->mlx_st);
	if (images->Y->mlx_st)
		mlx_destroy_image(mlx, images->Y->mlx_st);
}

void free_all_images2(t_all_images *images)
{
	if (images->I)
		free(images->I);
	if (images->X)
		free(images->X);
	if (images->T)
		free(images->T);
	if (images->Y)
		free(images->Y);
	if (images->blank_letter)
		free(images->blank_letter);
	if (images->color)
		free(images->color);
	if (images->background)
		free(images->background);
	if (images->number1)
		free(images->number1);
	if (images->number2)
		free(images->number2);
	if (images->terminal_sheet)
		free(images->terminal_sheet);
}

void free_all_images1(t_all_images *images)
{
	if (images->grass_wall_sheet)
		free(images->grass_wall_sheet);
	if (images->letters_sheet)
		free(images->letters_sheet);
	if (images->red_letters_sheet)
		free(images->red_letters_sheet);
	if (images->grass)
		free(images->grass);
	if (images->wall)
		free(images->wall);
	if (images->collectable)
		free(images->collectable);
	if (images->player)
		free(images->player);
	if (images->exit)
		free(images->exit);
	if (images->R)
		free(images->R);
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
}
void	end_game(t_all *all)
{
	mlx_loop_end(all->mlx);
	mlx_clear_window(all->mlx, all->window);
	mlx_destroy_window(all->mlx, all->window);
	free_map(all->map->map);
	if (all->map->map_adress)
		free(all->map->map_adress);
	if (all->game->element)
		free(all->game->element);
	if (all->terminal->user_pc_number)
		free(all->terminal->user_pc_number);
	if (all->terminal->user_name)
		free(all->terminal->user_name);
	free_structures(all);
	if (all->window_terminal)
	{
		mlx_clear_window(all->mlx, all->window_terminal);
		mlx_destroy_window(all->mlx, all->window_terminal);
	}
	if (all->mlx)
	{
		mlx_destroy_display(all->mlx);
		free(all->mlx);
	}
	free(all);
	exit (1);
}

int	parcing(char *argv1, t_all *all)
{
	if (!(check_map_ber_type(argv1)))
		return (0);
	all->map->map_name = argv1;
	all->map->map_adress = get_map_adress(argv1);
	if (!(all->map->map_adress))
		return (0);
	all->map->total_lines = count_lines(all->map->map_adress);
	if (!all->map->total_lines)
		return (0);
	all->map->map = create_map(all->map);
	if (!(all->map->map))
		return (0);
	if (!check_rectangle(all->map))
		return (0);
	if (!check_close_walls(all->map))
		return (0);
	if (!(check_elements(all->map, all->play, all->game, all->states)))
		return (0);
	if (!check_all_paths(all->map, all->play, all->game, all->states))
		return (0);
	if (!check_map_size(all))
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all 			*all;

	if (argc != 2)
	{
		write(2, "Error\nIncorret amount of arguments!\n", 36);
		return (1);
	}
	all = malloc (sizeof(t_all));
	if (!all)
	{
		write(2, "Error\nFailed struct \"ALL\" allocation", 36);
		return (1);
	}
	init_structures(all);
	general_settings(all);
	if (!(parcing(argv[1], all)))
	{
		write(2, "Error\nFailed due to wrong parsing", 33);
		end_game(all);
	}
	game_initializer(all);
}

// COMANDO PRA PEGAR O USER DA PESSOA e colocar num novo arquivo local
// name=$(ls -l | awk '{print $3}' | tail -1) && echo $name >> ./maps/user_name.ber

// COMANDO PRA PEGAR O COMPUTADOR DA PESSOA e colocar num novo arquivo local
// echo $HOST | cut -d'.' -f1 > ./maps/computer_number.ber

// compilar com
// cc -Wall -Wextra -Werror -I libft -I MiniLibX/minilibx-linux so_long.c libft/parcing.c libft/utils.c libft/getnextline.c -L MiniLibX/minilibx-linux -lmlx -lXext -lX11 -lm