/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp2.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:46:49 by olacerda          #+#    #+#             */
/*   Updated: 2025/08/30 16:35:16 by olacerda         ###   ########.fr       */
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
	int		st; 
	int		en;
	char	*lin;
	int		id;
	int		te;
	int		rb;
	char	buf[BUFFER_SIZE];
	char	*nl;
}	t_g;

typedef struct s_z
{
	char	*string;
	int		start;
	int		end;
} t_z;

char	*get_next_line(int fd);

#endif
