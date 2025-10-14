/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:57:14 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 00:29:50 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define BUFFER_SIZE 42
# define MAX_BUFFERSIZE 4000000

# include "so_long.h"
# include "../data/data.h"
# include "../core_game/core_game.h"

typedef struct s_g
{
	int		start;
	int		end;
	int		readbytes;
	char	buff[BUFFER_SIZE];
}			t_g;

int			check_all_paths(t_all *all, t_gameinfo *s_game, t_states *states);
int			path_to_colectable(char **map, int line, int column, int *tool);
// int			path_to_letters(char **map, int line, int column, 
	// char *to_colect, int *count);
int			letters_path(t_all *all, t_gameinfo *s_game, char **map,
				char *elements);
int			exit_colect_path(t_all *all, t_gameinfo *s_game, char **map,
				char *elements);
void		change_y_position(t_all *all, char **map, int flag);

int			strlength(char *string);
char		*getnextline(int fd);
void		liner(char **ln, t_g *x, int *endtotal);

int			check_rectangle(t_mapinfo *s_map);
int			check_close_walls(t_mapinfo *s_map);
int			check_map_size(t_all *all);

int			check_elements(t_mapinfo *s_map, t_gameinfo *s_game,
				t_states *states);
void		create_elements(t_gameinfo *s_game);
void		count_elements(t_mapinfo *s_map, t_gameinfo *s_game);
void		get_element_positions(t_gameinfo *game, t_mapinfo *map);

int			check_map_ber_type(char *name);
char		*get_map_adress(char *map_name, t_all *all);
int			check_map_adrees_need(char *map_name);

int			count_lines(char *chosen_map, t_all *all);
char		**create_map(t_mapinfo *map, t_all *all);
void		copy_map(t_mapinfo *map, char **copy, char *ignore);
int			parcing(char *argv1, t_all *all);

#endif
