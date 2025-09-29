/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:08:44 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/07 08:13:21 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
// int main(void)
// {
//     char    *line;

//     while (1)
//     {
//         line = getnextline(0);
//         if (!line)
//             break ;
// 		printf("You wrote: %s", line);
//         free(line);
//     }
// 	int fd1;
// 	int	fd2;
// 	int	fd3;

//     fd1 = open("./teste1.txt", O_RDONLY);
// 	fd2 = open("./teste2.txt", O_RDONLY);
// 	fd3 = open("./teste3.txt", O_RDONLY);

// 	char *line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     char *line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     char *line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);

//     close(fd1);
//     close(fd2);
//     close(fd3);
// 	printf("\n\nAfter close\n\n");

//     fd1 = open("./teste1.txt", O_RDONLY);
// 	fd2 = open("./teste2.txt", O_RDONLY);
// 	fd3 = open("./teste3.txt", O_RDONLY);

// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	line1 = getnextline(fd1);
//     printf("GET1:  %s\n", line1);
// 	free(line1);
//     line2 = getnextline(fd2);
//     printf("GET2:  %s\n", line2);
// 	free(line2);
//     line3 = getnextline(fd3);
//     printf("GET3:  %s\n", line3);
// 	free(line3);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// }
