/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:54:15 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/12 11:15:33 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef SO_LONG_H
# define SO_LONG_H
# define WIDE 64
# define TALL 64
# define COUNT 0
# define TARGET 1
# define LIMIT 2

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
	int	root;
	int	sound;
	int ub_count;
	int ub_count_backup;
	int	pc_number;
	int	allocation;
	int	root_speed;
	int	user_name;
} t_states;

typedef struct s_element
{
	char	charr;
	int		count;
	int		line;
	int		column;
	int		px_line;
	int		px_column;
	void	*mlx;
	char 	*img;
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
	int		usleep_save;
	int		shadow;
	char	*real_elements;
	int		elements_quantity;
	int		memory;
	int		ub_time;
	int		ub_current_time;
	int		exit_frame;
} t_gameinfo;

typedef struct s_terminalinfo
{
	int		pc_nb_size;
	int		pc_nb_size_save;
	int		current_line_size;
	int		wr_line;
	int		wr_index;
	char	*user_name;
	char	*user_pc_number;
	char 	*line_start;
	int		string_focused;
	char	writed[500][33];
} t_terminalinfo;

typedef struct s_playerinfo
{
	int	line;
	int	column;
	int p_line;
	int	p_column;
	int	pixel_line;
	int	pixel_column;
	int p_pixel_line;
	int	p_pixel_column;
	int	colected;
	int	lttrs_cnt;
	char	tl_range;
	char	tr_range;
	char	bl_range;
	char	br_range;
	int	F;
	int	I;
	int	R;
	int	A;
	int	frame;
	int	direction;
	int	movement;
	char	letter_colected[4];
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
    void *st;
    char *img;
	int	wide;
	int	tall;
    int bpp;
    int sizeline;
    int endian;
} t_image;

typedef struct s_all_images
{
	t_image *grass_wall_sheet;
	t_image *let_sheet;
	t_image *red_let_sheet;
	t_image *terminal_sheet;
	t_image *player_sheet;
	t_image *player_sheet_mirror;
	t_image *speed_player;
	t_image *speed_player_mirror;
	t_image *exit_sheet;
	t_image *collectable;
	t_image *grass;
	t_image *wall;
	t_image *player;
	t_image *exit;
	t_image *F;
	t_image *I;
	t_image *R;
	t_image *A;
	t_image *Y;
	t_image *color;
	t_image *background;
	t_image	*blank_letter;
	t_image *nbr1;
	t_image *nbr2;
} t_all_images;


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
} t_all;

# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "modules/core_game/core_game.h"
# include "modules/data/data.h"
# include "modules/graphic/graphic.h"
# include "modules/parsing/parsing.h"
# include "modules/terminal/terminal.h"


#endif