/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:09:23 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/18 10:32:21 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef UTILS_H
# define UTILS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX_BUFFERSIZE
#  define MAX_BUFFERSIZE 4000000
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>
# include "../so_long.h"	

typedef struct s_g
{
	int		start;
	int		end;
	int		readbytes;
	char	buff[BUFFER_SIZE];
}	t_g;


int		strlength(char *string);
void	putnumber(int nbr);
char	*getnextline(int fd);
void	liner(char **ln, t_g *x, int *endtotal);

int		check_rectangle(t_mapinfo *s_map);
int		check_close_walls(t_mapinfo *s_map);
int		check_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game);
int		check_path(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game);
int		check_file_name(char *name);


void 	create_elements(t_gameinfo *s_game);
void	count_elements(t_mapinfo *s_map, t_playerinfo *s_play, t_gameinfo *s_game);
int		path_to_colectable(char **map, int	line, int column, int *colectables);



#endif
