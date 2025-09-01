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

#include "temp.h"

char	*get_next_line(int fd)
{
	static t_g	x[FD_SETSIZE];

	x[fd].l = NULL;
	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	if (x[fd].r <= 0 || x[fd].s >= x[fd].r)
		x[fd] = (t_g){BUFFER_SIZE, BUFFER_SIZE, NULL, -1, 0, 1, {0}, NULL};
	while ((x[fd].l == NULL || x[fd].b[x[fd].e] != 10) && x[fd].r > 0)
	{
		((x[fd].s >= x[fd].r)) && (x[fd].r = read(fd, x[fd].b, BUFFER_SIZE));
		((x[fd].s >= x[fd].r)) && ((*(long *)&(x[fd]) = 0));
		while ((x[fd].b[x[fd].e] != 10) && (x[fd].e < x[fd].r) && ++(x[fd].e))
			(x[fd].t)++;
		x[fd].n = malloc(x[fd].t + 1 + (x[fd].b[x[fd].e] == 10) * sizeof(char));
		if (!x[fd].n)
			return (NULL);
		while (++x[fd].i < (x[fd].t - x[fd].e) && x[fd].l && x[fd].r > 0)
			x[fd].n[x[fd].i] = (x[fd].l)[x[fd].i];
		while ((x[fd].s <= x[fd].e) && (x[fd].s < x[fd].r) && x[fd].r > 0)
			x[fd].n[x[fd].i++] = x[fd].b[x[fd].s++];
		free(x[fd].l);
		*(t_r *)&(x[fd]) = (t_r){x[fd].s, x[fd].e, (void *)((long)x[fd].n * (x[fd].r > 0)), -1};
	}
	return (((x[fd].l != NULL) && (x[fd].n[x[fd].i] = 0)), x[fd].e += 
		(x[fd].b[x[fd].e]) == 10, x[fd].t = 0, x[fd].n = NULL, x[fd].l);
}

int main(void)
{
    char    *line;

    while (1)
    {
        line = get_next_line(0);
        if (!line)
            break ;
		printf("You wrote: %s", line);
        free(line);
    }
	int fd1;
	int	fd2;
	int	fd3;

    fd1 = open("./teste1.txt", O_RDONLY);
	fd2 = open("./teste2.txt", O_RDONLY);
	fd3 = open("./teste3.txt", O_RDONLY);

	char *line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    char *line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    char *line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);

    close(fd1);
    close(fd2);
    close(fd3);
	printf("\n\nAfter close\n\n");

    fd1 = open("./teste1.txt", O_RDONLY);
	fd2 = open("./teste2.txt", O_RDONLY);
	fd3 = open("./teste3.txt", O_RDONLY);

	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	line1 = get_next_line(fd1);
    printf("GET1:  %s\n", line1);
	free(line1);
    line2 = get_next_line(fd2);
    printf("GET2:  %s\n", line2);
	free(line2);
    line3 = get_next_line(fd3);
    printf("GET3:  %s\n", line3);
	free(line3);
	close(fd1);
	close(fd2);
	close(fd3);
}