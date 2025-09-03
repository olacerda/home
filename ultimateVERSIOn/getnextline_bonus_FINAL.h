/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_bonus_FINAL.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:38:18 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/02 16:22:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef BF
#  define BF BUFFER_SIZE
# endif
# ifndef MAX
#  define MAX 4000000
# endif
# define X x[fd]

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>

typedef struct s_g
{
	int		s; 
	int		e;
	char	*n;
	int		t;
	char	*ln;
	int		i;
	char	b[BUFFER_SIZE];
	int		rb;
}	t_g;

typedef struct s_w
{
	int		end;
	char	*nline;
	int		t;
	char	*line;
} t_w;

typedef struct s_y
{
	char	*string;
	int		index;
} t_y;

char	*get_next_line(int fd);

#endif
