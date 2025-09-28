/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_backup2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/17 17:08:04 by olacerda         ###   ########.fr       */
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
	adress = malloc((map_len + 6) * sizeof(char));
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

t_sheet *sheet_initiator(void *mlx, int	adress)
{
	t_sheet	*sheet;

	sheet = malloc(sizeof(t_sheet));
	if (!sheet)
		return (NULL);
	if (adress == 1)
		sheet->mlx_st = mlx_xpm_file_to_image(mlx, "textures/forest.xpm", &sheet->wide, &sheet->tall);
	if (adress == 2)
		sheet->mlx_st = mlx_xpm_file_to_image(mlx, "textures/Font-Pixels-01.xpm", &sheet->wide, &sheet->tall);	
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

void	sheet_to_image_convertor(t_sheet *src, t_image *dst, int sprite_number)
{
	int	bytes_per_line;
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;

	bytes_per_line = ((src->bpp * dst->wide) / 8);
	src_idx = (dst->sizeline * (sprite_number - 1));
	img_line = 0;
	count = 0;
	dst_idx = 0;
	printf("\nsrc_index: %d\nsrc_sizeline: %d\nsrc_tall: %d\ndst_sizeline %d\ndst_tall: %d\ndst_wide: %d\nsrc_bpp: %d\n\n", src_idx, src->sizeline, src->tall, dst->sizeline, dst->tall, dst->wide, src->bpp);
	if (src_idx > ((src->sizeline * src->tall) - (dst->sizeline * dst->tall)))
		return ;
	while (img_line < dst->tall)
	{
		count = 0;
		while(count < bytes_per_line)
		{
			dst->img[dst_idx++] = src->img[src_idx++];
			count++;
		}
		img_line++;
		src_idx = (img_line * src->sizeline) + (dst->sizeline * (sprite_number - 1));
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
	
	// images->e = image_initiator(mlx, 64, 64);
	// images->x = image_initiator(mlx, 64, 64);
	// images->i = image_initiator(mlx, 64, 64);
	// images->t = image_initiator(mlx, 64, 64);
	images->grass = image_initiator(mlx, 64, 64);
	images->wall = image_initiator(mlx, 64, 64);
	images->player = image_initiator(mlx, 64, 64);
	images->collectable = image_initiator(mlx, 64, 64);
	
	images->exit = image_initiator(mlx, 64, 64);
	sheet_to_image_convertor(images->grass_wall_sheet, images->wall, 1);
	sheet_to_image_convertor(images->grass_wall_sheet, images->grass, 2);
	color_image(images->player, 0);
	color_image(images->collectable, 501000);
	color_image(images->exit, 16711680);
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
				mlx_put_image_to_window(mlx, window, images->grass->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == '1')
				mlx_put_image_to_window(mlx, window, images->wall->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'P')
				mlx_put_image_to_window(mlx, window, images->player->mlx_st, index * 64, line * 64);
			if (map->map[line][index] == 'C')
				mlx_put_image_to_window(mlx, window, images->collectable->mlx_st, index * 64, line * 64);
			index++;
		}
		line++;
	}
}

void	update_images(void *mlx, void *window, t_all *all)
{
	mlx_put_image_to_window(mlx, window, all->images->grass->mlx_st, all->play->p_column * 64, all->play->p_line * 64);
	mlx_put_image_to_window(mlx, window, all->images->player->mlx_st, all->play->column * 64, all->play->line * 64);
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

void	update_game(t_all *all)
{
	if (all->map->map[all->play->line][all->play->column] == 'C' && all->states->full_colectables == 0)
	{
		write(1, "\a", 1);
		all->play->colected++;
		all->map->map[all->play->line][all->play->column] = '0';
	}
	// printf("COLECTED: %d\n", all->play->colected);
	if (all->play->colected >= all->game->count_elements[2] && all->states->full_colectables == 0)
	{
		all->states->full_colectables = 1;
		mlx_put_image_to_window(all->mlx, all->window, all->images->exit->mlx_st, all->game->e_column * 64, all->game->e_line * 64);	
	}
	if (all->states->full_colectables == 1 && all->map->map[all->play->line][all->play->column] == 'E')
	{
		all->states->full_colectables = 0;
		mlx_clear_window(all->mlx, all->window);
		mlx_destroy_window(all->mlx, all->window);
		exit (0);
	}
	mlx_do_sync(all->mlx);
}

int	callback(int code, void *arg)
{
	// (void)code;
	// (void)arg;
	t_all *all;

	all =(t_all *)arg;
	all->play->p_column = all->play->column;
	all->play->p_line = all->play->line;
	if (code == 100 && (all->map->map[all->play->line][all->play->column + 1] != '1'))
		all->play->column++;
	if (code == 97 && (all->map->map[all->play->line][all->play->column - 1] != '1'))
		all->play->column--;
	if (code == 119 && (all->map->map[all->play->line - 1][all->play->column] != '1'))
		all->play->line--;
	if (code == 115 && (all->map->map[all->play->line + 1][all->play->column] != '1'))
		all->play->line++;
	update_images(all->mlx, all->window, all);
	update_game(all);
	return (0);
}

int game_loop(void *arg)
{
    t_all *all;

    all = (t_all *)arg;
	if (all->states->full_colectables == 1)
		make_sound(250000);
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
	mlx_key_hook(all->window, callback, all);
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
	*s_play = (t_playerinfo){0, 0, 0, 0, 0};
	*s_game = (t_gameinfo){0, 0, 0, 0, 0};
	*states = (t_states){0, 0};
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
	if (!check_rectangle(s_map))
		return (1);
	if (!check_close_walls(s_map))
		return (1);
	if (!check_elements(s_map, s_play, s_game))
		return (1);
	if (!check_path(s_map, s_play, s_game))
		return (1);
	if (!check_map_size(all))
		return (1);
	game_initializer(s_map, all);
	free(s_map);
}

// compilar com
// cc -Wall -Wextra -Werror -I libft -I MiniLibX/minilibx-linux so_long.c libft/parcing.c libft/utils.c libft/getnextline.c -L MiniLibX/minilibx-linux -lmlx -lXext -lX11 -lm