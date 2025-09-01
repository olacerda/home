/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:37:25 by otlacerd          #+#    #+#             */
/*   Updated: 2025/08/27 10:57:47 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "getnextline_bonus_FINAL.h"

char	*get_next_line(int fd)
{
	static t_g	x;

	*(t_z *)&x = (t_z){NULL, x.index, 0};
	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	if (x.rb <= 0 || x.start >= x.rb)
		x = (t_g){NULL, -1, BUFFER_SIZE, BUFFER_SIZE, 0, 1, {0}, NULL};
	while ((x.line == NULL || x.buff[x.end] != 10) && x.rb > 0)
	{
		((x.start >= x.rb)) && (x.rb = read(fd, x.buff, BUFFER_SIZE));
		(x.start >= x.rb) && (*(long *)&((*(t_z *)&x).s) = 0);
		while ((x.buff[x.end] != 10) && (x.end < x.rb) && ++(x.end))
			++(x.tend);
		x.nline = malloc(x.tend + 1 + (x.buff[x.end] == 10) * sizeof(char));
		if (!x.nline)
			return (NULL);
		while (++x.index < (x.tend - x.end) && x.line && x.rb > 0)
			x.nline[x.index] = (x.line)[x.index];
		while ((x.start <= x.end) && (x.start < x.rb) && x.rb > 0)
			x.nline[x.index++] = x.buff[x.start++];
		x.nline[x.index] = '\0';
		free(x.line);
		*(t_z *)&(x) = (t_z){(void *)((long)x.nline * (x.rb > 0)), -1, x.start};
	}
	return (x.end += (x.buff[x.end]) == 10, x.nline = NULL, x.line);
}