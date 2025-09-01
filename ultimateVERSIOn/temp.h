/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:38:18 by otlacerd          #+#    #+#             */
/*   Updated: 2025/08/29 12:08:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX
#  define MAX 4000000
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/select.h>

typedef struct s_g
{
	int		s; 
	int		e;
	char	*l;
	int		i;
	int		t;
	int		r;
	char	b[BUFFER_SIZE];
	char	*n;
}	t_g;

typedef struct s_r
{
	int 	a;
	int		b;
	char 	*l;
	int		i;
}	t_r;

char	*get_next_line(int fd);

#endif
