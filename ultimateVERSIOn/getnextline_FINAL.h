/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline_FINAL.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:01:33 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/01 16:34:01 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
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
	char	*nline;
	int		totalend;
	int		rbts;
	char	buff[BUFFER_SIZE];
}	t_g;

typedef struct s_w
{
	char	*line;
	int		index;
	int		start; 
	int		end;
	char	*nline;
	int		tend;
} t_w;

typedef struct s_z
{
	char	*s;
	int		index;
} t_z;


char	*get_next_line(int fd);

#endif
