/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:30:01 by olacerda          #+#    #+#             */
/*   Updated: 2025/08/30 16:48:13 by olacerda         ###   ########.fr       */
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
	char	*line;
	int		index;
	int		start; 
	int		end;
	int		tend;
	int		rb;
	char	buff[BUFFER_SIZE];
	char	*nline;
}	t_g;

typedef struct s_z
{
	char	*string;
	int		index;
	int		s;
} t_z;

char	*get_next_line(int fd);

#endif
