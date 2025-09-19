/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_backup2.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:54:15 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/17 16:14:24 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct timeval t_time;

typedef struct s_states
{
	int	full_colectables;
	int	right_letters;
} t_states;

typedef struct s_gameinfo
{
	char	*elements;
	int		*count_elements;
	int		e_line;
	int		e_column;
	int		won;
} t_gameinfo;

typedef struct s_playerinfo
{
	int	line;
	int	column;
	int p_line;
	int	p_column;
	int	colected;
}	t_playerinfo;

typedef struct s_mapinfo
{
	char	**map;
	char	*map_name;
	char	*map_adress;
	int		total_lines;
	int		line_len;
}	t_mapinfo;

typedef struct s_image
{
    void *mlx_st;
    char *img;
	int	wide;
	int	tall;
    int bpp;
    int sizeline;
    int endian;
} t_image;

typedef struct s_sheet
{
	void *mlx_st;
	char *img;
	int	wide;
	int	tall;
    int bpp;
    int sizeline;
    int endian;
} t_sheet;

typedef struct s_all_images
{
	t_sheet *grass_wall_sheet;
	t_image *grass;
	t_image *wall;
	t_image *player;
	t_image *collectable;
	t_image *exit;
	t_sheet *letters_sheet;
	t_image *e;
	t_image *x;
	t_image *i;
	t_image *t;
} t_all_images;

typedef struct s_all
{
	t_mapinfo		*map;
	t_playerinfo	*play;
	t_all_images	*images;
	t_gameinfo		*game;
	t_states		*states;
	void			*mlx;
	void			*window;
} t_all;


# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/utils.h"



void 			so_long(t_mapinfo *s_map);
char			*get_map_adress(char *chosen_map);
int				count_lines(char *chosen_map);
char 			**create_map(t_mapinfo *s_map);
void			free_map(t_mapinfo *game);

t_sheet 		*sheet_initiator(void *mlx);
t_image			*image_initiator(void *mlx, int wide, int tall);
void			sheet_to_image_convertor(t_sheet *src, t_image *dst, int sprite_number);
t_all_images	*all_images_initiator(void *mlx);
void			color_image(t_image *image, int flag);

void			put_images(void *mlx, t_mapinfo *game, void *window, t_all_images *images);
void			game_initializer(t_mapinfo *s_map, t_all *all);
int				callback(int code, void *arg);
void			update_images(void *mlx, void *window, t_all *all);
void			update_game(t_all *all);

void 			make_sound(long frequency);
int				game_loop(void *arg);
int				check_map_size(t_all *all);

#endif