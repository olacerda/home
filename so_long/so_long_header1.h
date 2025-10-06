/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_header1.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:54:15 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/06 14:24:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef SO_LONG_H
# define SO_LONG_H
# define WIDE 64
# define TALL 64

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
	int	key_shift;
	int	key_ctrl;
	int	key_enter;
	int won;
	int	undefined_behavior;
	int	swifting_strings;
	int bonus;
	int	letters_compiled;
	int	pc_number;
} t_states;

typedef struct s_element
{
	char	charr;
	int		count;
	int		line;
	int		column;
	int		px_line;
	int		px_column;
	void	*str;
} t_element;

typedef struct s_gameinfo
{
	char	*elements;
	t_element *element;
	int		e_line;
	int		e_column;
	int		speed;
	int		speed2;
	int		usleep;
	int		shadow;
	char	*real_elements;
	int		elements_quantity;
	int		memory;
} t_gameinfo;

typedef struct s_terminalinfo
{
	int		pc_nb_size;
	int		current_line_size;
	int		wr_line;
	int		wr_index;
	char	*user_name;
	char	*user_pc_number;
	int		string_focused;
	char	writed[500][28];
} t_terminalinfo;

typedef struct s_playerinfo
{
	int	line;
	int	column;
	int p_line;
	int	p_column;
	int	colected;
	int	letters_colected_amount;
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
	void *st;
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
	t_image *Y;
	t_image *color;
	t_image *background;
	t_image	*blank_letter;
} t_all_images;

typedef struct s_all
{
	t_mapinfo		*map;
	t_playerinfo	*play;
	t_all_images	*images;
	t_gameinfo		*game;
	t_states		*states;
	t_terminalinfo	*terminal;
	void			*mlx;
	void			*window;
	void			*window_terminal;
	void			*window2;
} t_all;

typedef struct s_background
{
	int	ints_per_line;
	int	img_line;
	int src_idx;
	int	dst_idx;
	int	count;
	int	grid_line;
	int	grid_column;
	int	difference_line;
	int	difference_column;
	int	bg_idx;
	int bg_column;
	int	bg_line;
	char	*play;
	char	*grss;
} t_background;


# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/utils.h"



char			*get_map_adress(char *chosen_map);
int				count_lines(char *chosen_map);
char 			**create_map(t_mapinfo *s_map);
void			free_map(char **game);
int				check_map_adrees_need(char *map_name);


t_sheet 		*sheet_initiator(void *mlx, int sprite_number);
t_image			*image_initiator(void *mlx, int size, char charr, t_element *elements);
void			sheet_to_image(t_sheet *src, t_image *dst, t_image *banana, int nbr);
t_all_images	*all_images_initiator(void *mlx, t_all *all);
void			all_images_fill_buffers(t_all_images *images);
void			color_image(t_image *image, int flag);
t_background	*calculate_vars(t_all *all, t_sheet *src, int col, int line);
void			update_bg(t_sheet *src, t_all *all, int sprite_column, int sprite_line);
void			put_images(t_all *all, t_mapinfo *map, t_element *ele);
// void			check_bonus(t_all *all, char element, int line, int index);
void			put_letter(t_all *all, char *letters);

void			game_initializer(t_mapinfo *s_map, t_all *all);
int				update_position(void *arg);
void			update_images(t_all *all, int prev_px_col, int prev_px_line);
void			update_game(t_all *all);
void 			update_major_elements(t_all *all, int line, int column);
int				callback(t_all *all);
void			move_player(t_all *all, int *key_state, int yes, int no);
void			redefine_behavior(t_all *all);
void			redefine_behavior_directions(t_all *all, long *time, long *last);


void 			make_sound(long frequency);
int				game_loop(void *arg);
int				check_map_size(t_all *all);
void			check_letters_colected(t_all *all, char	element, int line, int column);

int				check_key_pressed(int	code, void *arg);
int				check_key_released(int code, void *arg);
int 			key_hook(int keycode, void *arg);


int				check_player_range(t_all *all, char element);
void			update_player_range(t_all *all, int line, int column);
int				check_hitbox(t_all *all, char element);
int				update_hitbox(t_all *all, int line, int column, char element);

long			get_full_time();
int				indexor(char *x);

void			general_settings(t_all *all);
void 			open_terminal(t_all *all);

int 			new_window_key_pressed(int keycode, void *arg);
int				new_window_key_released(int keycode, void *arg);
void			put_shift_character(t_all *all, int	code, int line);

void			get_username_and_pcnumber(t_all *all);
void			put_pcnumber_on_terminal(t_all *all, int line);
int				cmp_msg(t_all * all, char *string1, char *string2, int limit);
void			check_message(t_all *all, int line);
void			message_free(t_all *all, int line, char (*writed)[28]);
void			message_ls(t_all *all, int line, char (*writed)[28]);
void			put_string_on_terminal(t_all *all, char x, int line, int line_index);
void			switch_strings(t_all *all, int keycode, int line);
void			rebuild_current_map(t_all *all);




#endif