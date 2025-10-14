/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:11:22 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/13 22:29:57 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	strlength(char *string)
{
	int	length;

	if (!string)
		return (0);
	length = 0;
	while (string[length] != '\0' && string[length] != '\n')
		length++;
	return (length);
}

void	liner(char **ln, t_g *x, int *endtotal)
{
	char	*newline;
	int		index;

	if (x->readbytes <= 0)
		return ;
	if (x->start >= x->readbytes)
		*(long *)x = 0;
	while ((x->buff[x->end] != '\n') && (x->end < x->readbytes) && ++(x->end))
		(*endtotal)++;
	newline = malloc(*endtotal + 1 + (x->buff[x->end] == '\n') * sizeof(char));
	if (!newline)
		return ;
	index = -1;
	while (++index < (*endtotal - x->end) && *ln)
		newline[index] = (*ln)[index];
	while ((x->start <= x->end) && (x->start < x->readbytes))
		newline[index++] = x->buff[x->start++];
	newline[index] = '\0';
	free(*ln);
	*ln = newline;
}

char	*getnextline(int fd)
{
	static t_g	x[FD_SETSIZE];
	char		*ln;
	int			endtotal;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX_BUFFERSIZE)
		return (NULL);
	if (x[fd].readbytes <= 0 || x[fd].start >= x[fd].readbytes)
		x[fd] = (t_g){BUFFER_SIZE, 0, BUFFER_SIZE, {0}};
	ln = NULL;
	endtotal = 0;
	while ((x[fd].buff[x[fd].end] != '\n' || ln == NULL) && x[fd].readbytes > 0)
	{
		if (x[fd].start >= x[fd].readbytes)
			x[fd].readbytes = read(fd, x[fd].buff, BUFFER_SIZE);
		if (x[fd].readbytes == -1)
			return (free(ln), NULL);
		liner(&ln, &x[fd], &endtotal);
	}
	return (x[fd].end += (x[fd].buff[x[fd].end] == '\n'), ln);
}
