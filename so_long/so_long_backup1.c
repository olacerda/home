/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/14 01:18:12 by olacerda         ###   ########.fr       */
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

char **create_map(t_gameinfo *s_game)
{
	char	**map;
	int		line;
	int		fd;

	// printf("\nentrou no create_map\n");
	fd = open(s_game->map_adress, O_RDONLY);
	if (fd < 0)
		return (NULL);
	write(1, "passou", 6);
	// printf("\n LINES %d\n", s_game->total_lines);
	map = malloc ((s_game->total_lines + 1) * sizeof(char *));
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	line = 0;
	while(line < s_game->total_lines)
		map[line++] = getnextline(fd);
	map[line] = NULL;
	close(fd);
	return (map);
}

void	so_long(t_gameinfo *s_game)
{
	int		count = 0;

	if (!s_game->map)
		return ;
	while (s_game->map[count] != NULL)
	{
		printf("%s\n", s_game->map[count]);
		count++;
	}
}

// adicionar uma variável do tipo "int" para indicar qual "img" dentro da sheet vc está pegando
void	sheet_to_image_convertor(t_sheet *src, t_image *dst)
{
	int	bytes_per_line;
	int	img_line;
	int index;
	int	count;

	img_line = 0;
	index = 0;
	bytes_per_line = ((src->bpp * dst->wide) / 8);
	dst->img = malloc(dst->sizeline * dst->tall);
	if (!dst->img)
		return ;
	while (img_line < dst->tall)
	{
		count = 0;
		while(count < bytes_per_line)
		{
			dst->img[index] = src->img[index];
			index++;
			count++;
		}
		img_line++;
		index = img_line * dst->sizeline;
	}
}

void *sheet_initiator(void *mlx)
{
	t_sheet	*sheet;

	sheet = malloc(sizeof(t_sheet));
	if (!sheet)
		return ;
	sheet->mlx_st = mlx_xpm_file_to_image(mlx, "textures/forest.xpm", &sheet->wide, &sheet->tall);
	sheet->img = mlx_get_data_addr(sheet->mlx_st, &sheet->bpp, &sheet->sizeline, &sheet->endian);
	return (sheet);
}

void	*image_initiator(void *mlx, int wide, int tall)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	if (!image)
		return ;
	image->mlx_st = mlx_new_image(mlx, wide, tall);
	image->img = mlx_get_data_addr(image->mlx_st, &image->bpp, &image->sizeline, &image->endian);
	return (image);
}

void	all_images_initiator(void *mlx)
{
	t_image *grass;
	t_sheet	*wall_grass_sheet;

	grass = image_initiator(mlx, 64, 64);
	wall_grass_sheet = sheet_initiator(mlx);
}

void	game_initializer(t_gameinfo *s_game, t_playerinfo *s_play, t_mapinfo *s_map)
{
	void	*mlx;
	void	*window;
	void	*spritesheet_st;
	int		wide;
	int		tall;
	
	char	*spritesheet_img;
	char	*grass_img;
	void	*grass_st;
	int 	bpp;
	int		sizeline;
	int		endian;
	
	// vai ser deletado -------------------------------------------------------------
	
	spritesheet_st = mlx_xpm_file_to_image(mlx, "textures/forest.xpm", &wide, &tall);
	grass_st = mlx_new_image(mlx, 64, 64);
	spritesheet_img = mlx_get_data_addr(spritesheet_st, &bpp, &sizeline, &endian);
	grass_img = mlx_get_data_addr(grass_st, &bpp, &sizeline, &endian);
	
	//vai ser deletad --------------------------------------------------------------
	
	mlx = mlx_init();
	if (!mlx)
		exit (1);
	window = mlx_new_window(mlx, s_game->line_len * 64, s_game->total_lines * 64, s_game->map_name);
	if (!window)
		exit (1);
	mlx_loop(mlx);
}

int	main(int argc, char *argv[])
{
	t_gameinfo 		*s_game = malloc(sizeof(t_gameinfo));
	t_playerinfo	*s_play = malloc(sizeof(t_playerinfo));
	t_mapinfo		*s_map = malloc(sizeof(t_mapinfo));
	int				check_name;
	int				fd;

	if (argc != 2)
		return (1);
	s_game->map_name = argv[1];
	check_name = check_file_name(s_game);
	printf("\nCheck file name: %d\n", check_name);
	if (!check_name)
	{
		write(1, "aqui não!!!\n\n", 13);
		return (1);
	}
	*s_game = (t_gameinfo){0, 0, 0, 0, 0};
	*s_play = (t_playerinfo){0, 0};
	*s_map = (t_mapinfo){0, 0};
	s_game->map_adress = get_map_adress(argv[1]);
	printf("\nMap adress: %s\n", s_game->map_adress);
	s_game->total_lines = count_lines(s_game->map_adress);
	if (!s_game->total_lines)
	{
		write(1, "Falhou o total lines\n\n", 22);
		return (1);
	}
	printf("\nTotal lines: %d\n", s_game->total_lines);
	s_game->map = create_map(s_game);
	so_long(s_game);
	printf("\nCheck rectangle: %d\n", check_rectangle(s_game));
	printf("\nCheck close walls: %d\n", check_close_walls(s_game));
	printf("\nCheck Player/Colectabels/Exit: %d\n", check_elements(s_game, s_play, s_map));
	printf("\nCheck clear path: %d\n", check_path(s_game, s_play, s_map));
	printf("\nCheck file name: %d\n", check_name);
	fd = open(s_game->map_adress, O_RDONLY);
	printf("New FD: %d\n", fd);
	game_initializer(s_game, s_play, s_map);
	free(s_game);
	free(s_play);
	free(s_map);
}

// compilar com
// cc -Wall -Wextra -Werror -I libft -I MiniLibX/minilibx-linux so_long.c libft/parcing.c libft/utils.c libft/getnextline.c -L MiniLibX/minilibx-linux -lmlx -lXext -lX11 -lm 