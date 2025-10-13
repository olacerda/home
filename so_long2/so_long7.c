/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/06 14:24:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

char **create_map(t_mapinfo *s_map)
{
	char	**map;
	int		line;
	int		fd;

	fd = open(s_map->map_adress, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc ((s_map->total_lines + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	line = -1;
	while(++line < s_map->total_lines)
		map[line] = getnextline(fd);
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
	sheet->img = mlx_get_data_addr(sheet->st, &sheet->bpp, 
		&sheet->sizeline, &sheet->endian);
				
	printf("teste se entrou\n\n\n");
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
		elements[indexor(&charr)].str = image->mlx_st;
	if (!image->mlx_st)
		return (NULL);
	image->img = mlx_get_data_addr(image->mlx_st, &image->bpp, 
		&image->sizeline, &image->endian);
	if (!image->img)
		return (NULL);
	return (image);
}

void	sheet_to_image(t_sheet *src, t_image *dst, t_image *banana, int nbr)
{
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	int	ints_per_line;

	ints_per_line = ((src->bpp * dst->wide) / 32);
	src_idx = ((dst->sizeline / 4) * (nbr % (5))) + 
		((src->sizeline / 4) * ((nbr / (5)) * dst->tall));
	img_line = -1;
	dst_idx = 0;
	while (++img_line < dst->tall)
	{
		count = -1;
		while((++count < ints_per_line))
		{
			if (((int *)src->img)[src_idx] == -16777216)
				((int *)dst->img)[dst_idx] = ((int *)banana->img)[dst_idx];
			else
				((int *)dst->img)[dst_idx] = ((int *)src->img)[src_idx];
			dst_idx++;
			src_idx++;		
		}
		src_idx = src_idx + ((src->sizeline / 4) - (count));
	}
}

t_background	*calculate_vars(t_all *all, t_sheet *src, int col, int line)
{
	t_background 	*var;
	int				px_column;
	int 			px_line;

	var = malloc(sizeof(t_background));
	if (!var)
		return (NULL);
	px_column = all->game->element[indexor("P")].px_column;
	px_line = all->game->element[indexor("P")].px_line;
	var->grid_column = ((px_column / 64) * 64);
	var->grid_line = ((px_line / 64) * 64);
	var->difference_column = px_column - var->grid_column;
	var->difference_line = px_line - var->grid_line;
	var->ints_per_line = ((src->bpp * all->images->player->wide) / 32);
	var->src_idx = ((all->images->player->sizeline / 4) * (col - 1)) + 
		((src->sizeline / 4) * ((line - 1) * all->images->player->tall));
	var->bg_line = var->difference_column;
	var->bg_column = var->difference_line;
	var->img_line = 0;
	var->dst_idx = 0;
	var->bg_idx = 0;
	var->count = 0;
	var->play = all->images->player->img;
	var->grss = all->images->grass->img;
	return (var);
}

void	update_bg(t_sheet *src, t_all *all, int spr_column, int spr_line)
{
	t_background *x;

	x = calculate_vars(all, src, spr_column, spr_line);
	while ((x->img_line) < all->images->player->tall)
	{
		x->count = -1;
		while (++(x->count) < x->ints_per_line)
		{
			x->bg_line = (x->difference_column + x->count) % TALL;
			x->bg_column = (x->difference_line + x->img_line) % WIDE;
			x->bg_idx = (x->bg_column * (all->images->grass->sizeline / 4))
				 + x->bg_line;
			if (((int *)src->img)[x->src_idx] == -16777216)
				((int *)x->play)[x->dst_idx] = ((int *)x->grss)[x->bg_idx];
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

t_all_images	*all_images_initiator(void *mlx, t_all *all)
{
	t_all_images *images;

	images = malloc(sizeof(t_all_images));
	if (!images)
		return (NULL);
	images->grass_wall_sheet = sheet_initiator(mlx, 1);
	images->letters_sheet = sheet_initiator(mlx, 2);
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
	all_images_fill_buffers(images);
	return (images);
}

void	all_images_fill_buffers(t_all_images *images)
{
	sheet_to_image(images->grass_wall_sheet, images->wall, NULL, 0);
	sheet_to_image(images->grass_wall_sheet, images->grass, NULL, 1);
	sheet_to_image(images->letters_sheet, images->background, images->grass, 25);
	sheet_to_image(images->letters_sheet, images->player, images->grass, 25);
	color_image(images->collectable, 501000);
	color_image(images->exit, 0);
	color_image(images->color, 16711680);
	color_image(images->blank_letter, 0);
	sheet_to_image(images->letters_sheet, images->R, images->grass, 14);
	sheet_to_image(images->letters_sheet, images->X, images->grass, 33);
	sheet_to_image(images->letters_sheet, images->I, images->grass, 18);
	sheet_to_image(images->letters_sheet, images->T, images->grass, 29);
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
			while (map->map[ln][column] != ele[index++].charr)
				mlx_put_image_to_window(all->mlx, all->window, ele[index].str,
					column * 64, ln * 64);
			if ((map->map[ln][column] == 'R' || map->map[ln][column] == 'X' ||
				map->map[ln][column] == 'I' || map->map[ln][column] == 'T' ||
				map->map[ln][column] == 'E'|| map->map[ln][column] == 'P') ||
				 (map->map[ln][column] == 'Y' && all->states->bonus == 0)) 
			{
				all->map->map[ln][column] = '0';
				mlx_put_image_to_window(all->mlx, all->window, 
					all->game->element[indexor("0")].str, column * 64, ln * 64);
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
					all->game->element[indexor(&(map[line][index]))].str, 
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
		img_mlx = all->game->element[indexor(&(letters[index]))].str;
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
	void	*gr_mlx;
	void	*play_mlx;

	play_mlx = all->images->player->mlx_st;
	gr_mlx = all->images->grass->mlx_st;
	col = all->game->element[indexor("P")].px_column;
	line = all->game->element[indexor("P")].px_line;
	if (all->game->shadow == 1)
		mlx_put_image_to_window(all->mlx, all->window, gr_mlx, p_col, p_line);
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
        write(1, "\a", 1); // toca imediatamente
        return;
    }

    if (time - bell_last > frequency)
    {
        write(1, "\a", 1);
        bell_last = time;
    }
}

// void make_sound(long frequency)
// {
// 	static long time = 0;
// 	static long bell_last = 0;

// 	time = get_full_time();
// 	if (bell_last == 0)
// 		bell_last = time;
// 	if (time - bell_last > frequency)
// 	{
// 		write(1, "\a", 1);
// 		bell_last = time;
// 	}
// }

void	check_letters_colected(t_all *all, char	element, int line, int column)
{
	int			index;
	char *letters;

	letters = "RXIT";
	index = 0;
	if (element == 'R' || element == 'X' || element == 'I' || element == 'T')
	{
		all->play->letter_colected[all->play->letters_colected_amount] = 
			all->map->map[line][column];
		all->play->letters_colected_amount++;
		if (all->play->letters_colected_amount > all->game->memory)
			all->states->undefined_behavior = 1;
		while (index < all->play->letters_colected_amount)
		{
			if ((letters[index] != all->play->letter_colected[index]))
				return ;
			index++;
		}
	}
	if (all->play->letters_colected_amount == 4)
		all->states->right_letters = 1;	
}

int	update_hitbox(t_all *all, int line, int column, char elment)
{
	int		px_line;
	int		px_col;
	void	*gr_mlx;

	gr_mlx = all->images->grass->mlx_st;
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
			mlx_put_image_to_window(all->mlx, all->window, gr_mlx, px_col, 
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
//elements_quantity
void	update_player_range(t_all *all, int line, int column)
{
	char	**map;
	int		lin;
	int 	col;
	void	*element_buff;

	map = all->map->map;
	element_buff = all->game->element[indexor(&(map[line][column]))].str;
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
		update_player_range(all, ((line + 32) / 64), ((column + 32) / 64));
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
	if ((check_hitbox(all, 'E') == 1) && (all->states->won == 1))
	{
		all->states->full_colectables = 0;
		mlx_clear_window(all->mlx, all->window);
		mlx_destroy_window(all->mlx, all->window);
		exit (0);
	}
	if (all->states->full_colectables == 1 && all->states->right_letters == 1 &&
			all->states->won == 0)
	{
		all->states->won = 1;
		all->map->map[line][column] = 'E';
		mlx_put_image_to_window(all->mlx, all->window, exit_mlx, column * 64, 
			line * 64);
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
	if (*time - *last > 2700000)
	{
		all->game->usleep = 65000;
		(all->game->speed < 0) && (all->game->speed = -16);
		(all->game->speed > 0) && (all->game->speed = 16);
		(all->game->speed2) = -(all->game->speed2);
		sheet_to_image(all->images->letters_sheet, all->images->background, 
			all->images->grass, 25);
	}
	if (*time - *last > 3700000)
		(all->game->speed2) = -(all->game->speed2);
	if (*time - *last > 4700000)
	{
		(all->game->speed2) = -(all->game->speed2);
		(all->game->speed) = -(all->game->speed);
		*last = *time;
	}
}

void	redefine_behavior(t_all *all)
{
		static long time = 0;
		static long last = 0;

		time = get_full_time();
		if (all->game->speed == 2)
		{
			all->game->shadow = 1;
			all->game->usleep = 65000;
			(all->game->speed) = 16;
			last = time;
		}
		if (time - last > 2000000)
		{
			all->game->usleep = 45000;
			(all->game->speed < 0) && (all->game->speed = -48);
			(all->game->speed > 0) && (all->game->speed = 48);
			color_image(all->images->background, 0);
		}
		redefine_behavior_directions(all, &time, &last);
}

void	move_player(t_all *all, int *key_state, int yes, int no, int speed, int sped2)
{
	int	line;
	int	col;
	char **map;

	map = all->map->map;
	if (all->states->undefined_behavior == 1)
		redefine_behavior(all);
	line = all->game->element[indexor("P")].px_line;
	col = all->game->element[indexor("P")].px_column;
	if ((key_state[0] == 1) && (map[(line + no - speed) / 64][(col + no) / 64]
		 != '1') && (map[(line + no - speed) / 64][(col + yes) / 64] != '1'))
		all->game->element[indexor("P")].px_line -= speed;
	else if ((key_state[0] == 1) && (map[(line + no - sped2) / 64][(col + no) /
		64] != '1') && (map[(line + no - sped2) / 64][(col + yes) / 64] != '1'))
		all->game->element[indexor("P")].px_line -= sped2;
	if ((key_state[1] == 1) && (map[(line + no) / 64][(col + no - speed) / 64]
		!= '1') && (map[(line + yes) / 64][(col + no - speed) / 64] != '1'))
		all->game->element[indexor("P")].px_column -= speed;
	else if ((key_state[1] == 1) && (map[(line + no) / 64][(col + no - sped2) /
		64] != '1') && (map[(line + yes) / 64][(col + no - sped2) / 64] != '1'))
		all->game->element[indexor("P")].px_column -= sped2;
}

int	callback(t_all *all)
{
	int	keycode[2];
	int	yes;
	int	no;

	yes = 63 * (all->game->speed > 0);
	no = 63 * (all->game->speed < 0);
	keycode[0] = 0;
	keycode[1] = 0;
	all->play->p_pixel_column = all->game->element[indexor("P")].px_column;
	all->play->p_pixel_line = all->game->element[indexor("P")].px_line;
	if (all->states->terminal != 1)
	{
		keycode[0] = all->states->key_w;
		keycode[1] = all->states->key_a;
		move_player(all, keycode, yes, no, all->game->speed, all->game->speed2);
		keycode[0] = all->states->key_s;
		keycode[1] = all->states->key_d;
		move_player(all, keycode, no, yes, -(all->game->speed), -(all->game->speed2));
	}
	all->game->element[indexor("P")].column = all->game->element[indexor("P")].px_column / 64;
	all->game->element[indexor("P")].line = all->game->element[indexor("P")].px_line / 64;                                              
	return (0);
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

int	compare_message(t_all * all, char *string1, char *string2, int limit)
{
	int	index1;
	int	index2;

	index1 = 0;
	index2 = all->terminal->pc_nb_size;
	printf("Str1 char: %c   ------- str2 char: %c\n\n", string1[index1], string2[index2]);
	while(string2[index2] != '_' && string1[index1] && string2[index2] && 
		string1[index1] == string2[index2] && limit > 0)
	{
		printf("\ncomparason between: -------------------------------------->>>>> %c and %c\n\n", string1[index1], string2[index2]);
		index1++;
		index2++;
		limit--;
	}
	if (string2[index2] == '_' || (string2[index2] == '\0') || (string2[index2] >= 48 && string2[index2] <= 57))
		index2--;
	if (index1 > 0)
		index1--;
	printf("Returning: ----------------------------------->>>>>>>%c (%d)  minus  %c (%d)\n\n", string1[index1], string1[index1], string2[index2], string2[index2]);
	return (string1[index1] - string2[index2]);
}

void	check_message(t_all *all, int *line)
{
	int	size;
	int	index;
	char	*to_write;

	to_write = NULL;
	index = all->terminal->pc_nb_size;
	size = 0;
	while (all->terminal->writed[*line][index] && all->terminal->writed[*line][index] != '_')
	{
		index++;
		size++;
	}
	printf("Size:------------------------------->>>>>>>>>> %d\n", size);
	if ((size == 12) && (compare_message(all, "free(memory)", all->terminal->writed[*line], 12) == 0))
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
		return ;
	}
	else if ((size == 9) && (compare_message(all, "malloc(", all->terminal->writed[*line], 8) == 0))
	{
		all->game->memory = (all->terminal->writed[*line][all->terminal->pc_nb_size + 7] - 48);
		return ;
	}
	else if ((size == 7) && (all->states->letters_compiled == 1) && (compare_message(all, "./a.out", all->terminal->writed[*line], 7) == 0))
	{
		put_letter(all, "RXIT");
	}
	else if ((size == 12) && (compare_message(all, "cc letters.c", all->terminal->writed[*line], 12)) == 0)
	{
		all->states->letters_compiled = 1;
	}
	else if ((size == 2) && (compare_message(all, "ls", all->terminal->writed[*line], 2)) == 0)
	{
		all->terminal->wr_line++;
		all->terminal->wr_index = 0;
		if (all->states->letters_compiled == 0)
			to_write = "letters.c";
		else
			to_write = "letters.c   a.out";
		while (to_write[all->terminal->wr_index])
		{
			all->terminal->writed[*line][all->terminal->wr_index] = to_write[all->terminal->wr_index];
			all->terminal->wr_index++;
		}
		all->terminal->writed[*line][all->terminal->wr_index] = '\0';
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[all->terminal->wr_line]);	
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

//COLECTED

void	put_shift_character(t_all *all, int	code, int line)
{
	(void)line;
	if (code == 57)
	{
		all->terminal->writed[line][all->terminal->wr_index] = '(';
        all->terminal->writed[line][all->terminal->wr_index + 1] = '_';
        all->terminal->writed[line][all->terminal->wr_index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->wr_index) * 6), (30 + (5 * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[line]);
		all->terminal->wr_index++;
	}
	if (code == 48)
	{
        all->terminal->writed[line][all->terminal->wr_index] = ')';
        all->terminal->writed[line][all->terminal->wr_index + 1] = '_';
        all->terminal->writed[line][all->terminal->wr_index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 11 + ((all->terminal->wr_index) * 6), (30 + (5 * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[line]);
		all->terminal->wr_index++;
	}
}

//adaptar os códigos para diferentes tipos de teclado.... shift 8, e shift 9 são para windows PT-BR, verificar os teclados dos 2 clusters da 42.

                                  //       IMPORTANTE

// pra cima 65362
// pra baixo 65364
void	put_string_on_terminal(t_all *all, char x, int line, int line_index)
{
	int	count;

	count = 0;
	(void)x;
	(void)line_index;
	(void)line;
	mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 0, 10);
	while (count < 5)
	{
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + ((count) * 20), 16711680, all->terminal->writed[line - 4 + count]);
		count++;
	}
}

void	switch_strings(t_all *all, int keycode, int line)
{
	int	index2;
	// int	focused;

	index2 = 0;
	if (all->states->swifting_strings == 0 && keycode == 65362 && all->terminal->string_focused != 5)
	{
		while ((all->terminal->writed[line][all->terminal->current_line_size] != '_') && all->terminal->writed[line][all->terminal->current_line_size])
		{
			all->terminal->writed[line + 1][all->terminal->current_line_size] = all->terminal->writed[line][all->terminal->current_line_size];
			all->terminal->current_line_size++;
		}
		// all->terminal->writed[line + 1][all->terminal->current_line_size] = '\0';
		all->states->swifting_strings = 1;
	}
	
	if ((keycode == 65362) && (all->terminal->string_focused > 5))
	{
		all->terminal->string_focused--;
		if (all->terminal->string_focused == line && (all->terminal->string_focused > 5))
			all->terminal->string_focused--;
		while ((all->terminal->writed[all->terminal->string_focused][0] != 'c') && (all->terminal->string_focused > 5))
			all->terminal->string_focused--;
	}
	else if ((keycode == 65364) && (all->terminal->string_focused < line + 1) && (all->states->swifting_strings == 1))
	{
		all->terminal->string_focused++;
		if (all->terminal->string_focused == line && all->terminal->string_focused < (line + 1))
			all->terminal->string_focused++;
		while ((all->terminal->writed[all->terminal->string_focused][0] != 'c') && all->terminal->string_focused < (line))
			all->terminal->string_focused++;
	}
	// focused = all->terminal->string_focused;
	while (all->terminal->writed[all->terminal->string_focused][index2] && (index2 < 28))
	{
		all->terminal->writed[line][index2] = all->terminal->writed[all->terminal->string_focused][index2];
		index2++;
	}
	all->terminal->writed[line][index2] = '\0';
	all->terminal->wr_index = index2;
	printf("INDEX 1 AQUI---------------->>>: %d\n\n", all->terminal->current_line_size);
	printf("Focused: %d\nLine: %d\n", all->terminal->string_focused, line);
	mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 0, (30 + (5 * 20)) - 10);
	mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[line]);
}
				
// void	reset_terminal_lines(t_all *all)
// {
// 	int top_line;
// 	int	index;

// 	index = 0;
// 	top_line = 494;
// 	while (top_line < 499)
// 	{
// 		all.
// 	}
// }
//undefined
void	put_pcnumber_on_terminal(t_all *all, int line)
{
	int	index;

	index = 0;
	all->terminal->wr_index = 0;
	while (all->terminal->user_pc_number[all->terminal->wr_index])
	{
		all->terminal->writed[line][all->terminal->wr_index] = all->terminal->user_pc_number[index];
		index++;
		all->terminal->wr_index++;
	}
	all->terminal->writed[line][(all->terminal->wr_index)++] = ' ';
	all->terminal->writed[line][all->terminal->wr_index] = '\0';
}


int new_window_key_pressed(int keycode, void *arg)
{
	t_all *all;

	// printf("key pressed: %d\n", keycode);
	all = (t_all *)arg;
	printf("Linha escrita: %s\nNumero da linha: %d\n\n\n", all->terminal->writed[all->terminal->wr_line], all->terminal->wr_line);
	// static int	all->terminal->writed_line = 10;
	// static int	column = 30;
	if (keycode == 65505 || keycode == 65506)
		all->states->key_shift = 1;
	if (keycode == 65507 || keycode == 65508)
		all->states->key_ctrl = 1;
	if ( (all->terminal->wr_index < 27) && all->states->key_shift == 1 && (keycode == 57 || keycode == 48))
		put_shift_character(all, keycode, all->terminal->wr_line);
	else if ((keycode == 65362) || (keycode == 65364))
		switch_strings(all, keycode, all->terminal->wr_line);
    else if ((all->terminal->wr_index < 27) && (all->states->key_shift == 0)  && (all->states->key_ctrl == 0) && 
		((keycode >= 0 && keycode <= 25) || (keycode >= 97 && keycode <= 122) || (keycode == 32) || (keycode >= 48 && keycode <= 57)
		|| (keycode == 46) || (keycode == 47)))
	{
		// insert_pcnumber(all, all->terminal->writed_line);
        all->terminal->writed[all->terminal->wr_line][all->terminal->wr_index] = (char)keycode;
        all->terminal->writed[all->terminal->wr_line][all->terminal->wr_index + 1] = '_';
        all->terminal->writed[all->terminal->wr_line][all->terminal->wr_index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->wr_index) * 6), (30 + (5 * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[all->terminal->wr_line]);
		all->terminal->wr_index++;
		// all->states->swifting_strings = 0;
	}
	else if (keycode == 65288 && all->terminal->wr_index > all->terminal->pc_nb_size)
	{
		all->terminal->writed[all->terminal->wr_line][all->terminal->wr_index] = '\0';
		if (all->terminal->wr_index > 0)
			all->terminal->wr_index--;
		all->terminal->writed[all->terminal->wr_line][all->terminal->wr_index] = '_';
		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->wr_index) * 6), (30 + (5 * 20)) - 10);
		mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[all->terminal->wr_line]);
	}
	// if (keycode == 65307)
    else if (keycode == 65293)
	{
		// if (all->states->terminal_hook_flag == 1)
		// 	all->states->terminal_hook_flag = 0;
		check_message(all, &all->terminal->wr_line);
		// all->terminal->writed_index--;
		// mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->writed_index) * 6), (30 + (all->terminal->writed_line * 20)) - 10);
		// printf("all->terminal->writed_line no mini-terminal %d\n", all->terminal->writed_line);
		// all->terminal->writed[all->terminal->writed_line][all->terminal->writed_index] = '_';
		all->terminal->writed[all->terminal->wr_line][all->terminal->wr_index] = '\0';
		all->terminal->writed[all->terminal->wr_line + 1][all->terminal->wr_index] = '\0';
		put_string_on_terminal(all, 'x', all->terminal->wr_line, 0);
		all->terminal->wr_line++;
		if (all->terminal->wr_line >= 20)
			all->terminal->wr_line = 5;
		all->terminal->string_focused = all->terminal->wr_line;
		all->terminal->current_line_size = 0;
		all->terminal->wr_index = 0;
		all->states->swifting_strings = 0;
		// int	teste;
		// teste = (compare_message("ls", all->terminal->writed[(all->terminal->writed_line)], 2));
		// printf("RESULTADO DO COMPARE COM LS: %d\n\n", teste);
		//8
		//&& ((compare_message("ls", all->terminal->writed[(all->terminal->writed_line) - 1], 2)) != 0)
		if (all->terminal->wr_index == 0)
		{
			put_pcnumber_on_terminal(all, all->terminal->wr_line);
			mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[all->terminal->wr_line]);
		}
		// mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->writed_index) * 6), (30 + (all->terminal->writed_line * 20)) - 10);
		// mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (all->terminal->writed_line * 20), 16711680, all->terminal->writed);
		// usleep(10000);
		// else if (all->states->terminal_hook_flag == 0)
		// {
			// }
	}
	if (all->states->key_ctrl == 1 && keycode == 99)
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
		// all->states->terminal_hook_flag = 0;
		
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
//         all->terminal->writed[all->terminal->writed_index] = (char)keycode;
//         all->terminal->writed[all->terminal->writed_index + 1] = '_';
//         all->terminal->writed[all->terminal->writed_index + 2] = '\0';
// 		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->writed_index) * 6), line);
// 		mlx_string_put(all->mlx, all->window_terminal, 10, 30, 16711680, all->terminal->writed);
// 		all->terminal->writed_index++;
// 	}
// 	if (keycode == 65288)
// 	{
// 		all->terminal->writed[all->terminal->writed_index] = '\0';
// 		if (all->terminal->writed_index > 0)
// 			all->terminal->writed_index--;
// 		all->terminal->writed[all->terminal->writed_index] = '_';
// 		mlx_put_image_to_window(all->mlx, all->window_terminal, all->images->blank_letter->mlx_st, 10 + ((all->terminal->writed_index) * 6), 21);
// 		mlx_string_put(all->mlx, all->window_terminal, 10, 30, 16711680, all->terminal->writed);
// 	}
// 	// if (keycode == 65307)
// 	if (keycode == 65293)
// 	{
// 		if (all->states->terminal_hook_flag == 1)
// 			all->states->terminal_hook_flag = 0;
// 		else if (all->states->terminal_hook_flag == 0)
// 		{
// 			check_message(all);
// 			all->terminal->writed_index = 0;
// 			all->terminal->writed[all->terminal->writed_index] = '\0';
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
		all->window_terminal = mlx_new_window(all->mlx, 180, 140, all->terminal->user_name);
		// mlx_key_hook(all->window_terminal, key_hook, all);
		mlx_hook(all->window_terminal, 2, 1L<<0, new_window_key_pressed, all);
		mlx_hook(all->window_terminal, 3, 1L<<1, new_window_key_released, all);
		// if (all->states->terminal_hook_flag == 1)
		// {
		// 	all->states->terminal_hook_flag = 0;
		// }
        // mlx_hook(all->window_terminal, 2, 1L<<0, key_hook, all);

		
		if (all->terminal->wr_index == 0)
		{
			put_pcnumber_on_terminal(all, all->terminal->wr_line);
			mlx_string_put(all->mlx, all->window_terminal, 10, 30 + (5 * 20), 16711680, all->terminal->writed[all->terminal->wr_line]);
		}
			
        mlx_string_put(all->mlx, all->window_terminal, 10, 10, 16711680, "Comand:\n");
    }
}

int game_loop(void *arg)
{
    t_all *all = (t_all *)arg;

	printf("Real time: %li\n\nUndefined behavior state: %d\n\n", get_full_time(), all->states->undefined_behavior);
    if (all->states->terminal == 1)
    {
        open_terminal(all);
        // all->states->terminal = 0;
    }
	if (all->states->undefined_behavior == 1)
	{
		make_sound(200000);
		// printf("é undefined behavior!!!");
	}
    if ((all->states->key_a != 0 || all->states->key_w != 0 || 
         all->states->key_s != 0 || all->states->key_d != 0) && all->states->terminal == 0)
    {
        callback(all);
        update_bg(all->images->letters_sheet, all, 1, 6);
		check_player_range(all, '0');
    }
	update_game(all);                                               
	if (all->game->shadow == 1)
		mlx_put_image_to_window(all->mlx, all->window, all->images->background->mlx_st, all->play->p_pixel_column, all->play->p_pixel_line);
	mlx_put_image_to_window(all->mlx, all->window, all->images->player->mlx_st, all->game->element[indexor("P")].px_column, all->game->element[indexor("P")].px_line);
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
	printf("passou aqui\n\n\n\n");
	if (!all->terminal->user_name)
		all->terminal->user_name = "TERMINAL";
	close(fd);
	fd = open("./maps/computer_number.ber", O_RDONLY);
	all->terminal->user_pc_number = getnextline(fd);
	all->states->pc_number = 1;
	while(all->terminal->user_pc_number[size])
		size++;
	all->terminal->pc_nb_size = size + 1;
	if (!all->terminal->user_pc_number)
	{
		all->terminal->user_pc_number = "comand: ";
		all->terminal->pc_nb_size = size + 1;
		all->states->pc_number = 0;
	}
}

void game_initializer(t_mapinfo *s_map, t_all *all)
{
    t_all_images *images;

    all->mlx = mlx_init();
    if (!all->mlx)
		exit(1);
	images = all_images_initiator(all->mlx, all);
	get_username_and_pcnumber(all);
    all->images = images;
    all->window = mlx_new_window(all->mlx, s_map->line_len * 64, s_map->total_lines * 64, s_map->map_name);
    if (!all->window)
        exit(1);

    all->window_terminal = NULL; // Inicializa como NULL
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
//check_map


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
	// if (all->images)
	// 	all->images->background = all->images->grass;
	if (flag == 1)
	{
		while (all->game->real_elements[count])
			count++;
		all->game->elements_quantity = count;
		indexor(all->game->real_elements);
		flag = 0;
	}
}
	//writed_index;
	//user_name;
	//user_pc_number;
	//string_focused;
	//writed[500][28];
//check_map_ber_type
int	main(int argc, char *argv[])
{
	t_all 			*all = malloc(sizeof(t_all));
	t_playerinfo	*s_play = malloc(sizeof(t_playerinfo));
	t_mapinfo		*s_map = malloc(sizeof(t_mapinfo));
	t_gameinfo		*s_game = malloc(sizeof(t_gameinfo));
	t_states		*states = malloc(sizeof(t_states));
	t_terminalinfo 	*terminal = malloc(sizeof(t_terminalinfo));

	if (argc != 2)
		return (1);
	*s_map = (t_mapinfo){0, 0, 0, 0, 0};
	*s_play = (t_playerinfo){0, 0, 0, 0, 0, 0, {0}, 0, 0, 0, 0, '\0', '\0', '\0', '\0', 0, 0, 0, 0};
	*s_game = (t_gameinfo){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	*states = (t_states){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	*terminal = (t_terminalinfo){0, 0, 5, 0, 0, 0, 5, {{0}}};
	all->terminal = terminal;
	all->map = s_map;
	all->play = s_play;
	all->game = s_game;
	all->states = states;
	all->window2 = NULL;
	general_settings(all);
	if (!(check_map_ber_type(argv[1])))
		return (1);
	s_map->map_name = argv[1];
	s_map->map_adress = get_map_adress(argv[1]);
	if (!(s_map->map_adress))
		return (1);
	// printf("Map adress123: %s\n\n\n", s_map->map_adress);
	s_map->total_lines = count_lines(s_map->map_adress);
	if (!s_map->total_lines)
		return (1);
	// write(1, "teste\n", 6);
	s_map->map = create_map(s_map);
	if (!(s_map->map))
		return (1);
	printf("\nPassou aqui\n");
	if (!check_rectangle(s_map))
		return (1);
	if (!check_close_walls(s_map))
		return (1);
	if (!(check_elements(s_map, s_play, s_game, states)))
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
	if (!check_all_paths(s_map, s_play, s_game, states))
		return (1);
	// write(1, "teste123", 5);
	if (!check_map_size(all))
		return (1);
	game_initializer(s_map, all);
	printf("EU AQUI------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	free(s_map);
}
//e_linefree_m

// COMANDO PRA PEGAR O USER DA PESSOA e colocar num novo arquivo local
// name=$(ls -l | awk '{print $3}' | tail -1) && echo $name >> ./maps/user_name.ber

// COMANDO PRA PEGAR O COMPUTADOR DA PESSOA e colocar num novo arquivo local
// echo $HOST | cut -d'.' -f1 > ./maps/computer_number.ber

// compilar com
// cc -Wall -Wextra -Werror -I libft -I MiniLibX/minilibx-linux so_long.c libft/parcing.c libft/utils.c libft/getnextline.c -L MiniLibX/minilibx-linux -lmlx -lXext -lX11 -lm