/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_backup6.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:54:15 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/27 03:49:44 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct timeval t_time;

typedef struct s_states
{
	int	full_colectables;
	int	right_letters;
	int	terminal;
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_enter;
	int	terminal_hook_flag;
} t_states;

typedef struct s_element
{
	char	charr;
	int		count;
	int		line;
	int		column;
	int		px_line;
	int		px_column;
} t_element;

typedef struct s_gameinfo
{
	char	*elements;
	t_element *element;
	// int		*count_elements;
	int		e_line;
	int		e_column;
	int		won;
	int		speed;
	int		usleep;
	int		shadow;
	char	*real_elements;
	int		elements_quantity;
	char	writed[10000];
} t_gameinfo;

typedef struct s_playerinfo
{
	int	line;
	int	column;
	int p_line;
	int	p_column;
	int	colected;
	char	letter_colected[4];
	int	pixel_line;
	int	pixel_column;
	int p_pixel_line;
	int	p_pixel_column;
	char	tl_range;
	char	tr_range;
	char	bl_range;
	char	br_range;
	int	R;
	int	X;
	int	I;
	int	T;
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
	t_image *R;
	t_image *X;
	t_image *I;
	t_image *T;
	t_image *color;
	t_image *background;
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
	void			*window_terminal;
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
void			free_map(char **game);

t_sheet 		*sheet_initiator(void *mlx, int sprite_number);
t_image			*image_initiator(void *mlx, int wide, int tall);
void			sheet_to_image_convertor(t_sheet *src, t_image *dst, t_image *background, int sprite_column, int sprite_line);
t_all_images	*all_images_initiator(void *mlx);
void			color_image(t_image *image, int flag);
void			update_background(t_sheet *src, t_image *dst, t_image *background, int sprite_column, int sprite_line, t_gameinfo *game);
void			put_images(void *mlx, t_mapinfo *game, void *window, t_all_images *images);

void			game_initializer(t_mapinfo *s_map, t_all *all);
int				update_position(void *arg);
void			update_images(void *mlx, void *window, t_all *all, int previous_pixel_column, int previous_pixel_line);
void			update_game(t_all *all);

void 			make_sound(long frequency);
int				game_loop(void *arg);
int				check_map_size(t_all *all);
void			check_letters_colected(t_all *all, char	element, int line, int column);

int				check_key_pressed(int	code, void *arg);
int				check_key_released(int code, void *arg);
int 			key_hook(int keycode, void *arg);


void			update_player_range(t_all *all);
void			update_hitbox_range(t_all *all, int	line, int column);
int				check_player_range(t_all *all, char element);
int				check_hitbox(t_all *all, char element);

long			get_full_time();

int				indexor(char *x);

void			general_settings(t_all *all);
void 			open_terminal(t_all *all);



#endif