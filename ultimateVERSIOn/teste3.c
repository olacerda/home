/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:25:41 by olacerda          #+#    #+#             */
/*   Updated: 2025/08/30 17:00:27 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "getnextline_FINAL.h"

char	*get_next_line(int fd)
{
	static t_g	x;

	x.line = NULL;
	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	if (x.rb <= 0 || x.s >= x.rb)
		x = (t_g){BUFFER_SIZE, BUFFER_SIZE, NULL, -1, 0, 1, {0}, NULL};
	while ((x.line == NULL || x.buff[x.e] != 10) && x.rb > 0)
	{
		((x.s >= x.rb)) && (x.rb = read(fd, x.buff, BUFFER_SIZE));
		(x.s >= x.rb) && (*(long *)&(x) = 0);
		while ((x.buff[x.e] != 10) && (x.e < x.rb) && ++(x.e))
			++(x.totalend);
		x.nlin = malloc(x.totalend + 1 + (x.buff[x.e] == 10) * sizeof(char));
		if (!x.nlin)
			return (NULL);
		while (++x.index < (x.totalend - x.e) && x.line && x.rb > 0)
			x.nlin[x.index] = (x.line)[x.index];
		while ((x.s <= x.e) && (x.s < x.rb) && x.rb > 0)
			x.nlin[x.index++] = x.buff[x.s++];
		x.nlin[x.index] = '\0';
		free(x.line);
		*(t_z *)&(x) = (t_z){x.s, x.e, (void *)((long)x.nlin * (x.rb > 0)), -1};
	}
	return (x.e += (x.buff[x.e]) == 10, x.totalend = 0, x.nlin = NULL, x.line);
}

int	main(void)
{
	int fd;
	char *line1 = "";

	fd = open("./teste1.txt", O_RDONLY);
	while (line1 != NULL)
	{
		line1 = get_next_line(0);
		if(line1 != NULL)
			printf("You wrote ->%s", line1);
		free(line1);
	}
	printf("open %i\n", fd);
	line1 = get_next_line(fd);
	printf("GET1:  %s\n", line1);
	free(line1);
	char *line2 = get_next_line(fd);
	printf("GET2:  %s\n", line2);
	free(line2);
	char *line3 = get_next_line(fd);
	printf("GET3:  %s\n", line3);
	free(line3);
	char *line4 = get_next_line(fd);
	printf("GET4:  %s\n", line4);
	free(line4);
	char *line5 = get_next_line(fd);
	printf("GET5:  %s\n\n", line5);
	free(line5);
	printf("After close:\n\n");

	close(fd);
	fd = open("./teste1.txt", O_RDONLY);
	printf("open %i\n", fd);
	line1 = get_next_line(fd);
	printf("GET1:  %s\n", line1);

	line2 = get_next_line(fd);
	printf("GET2:  %s\n", line2);

	line3 = get_next_line(fd);
	printf("GET3:  %s\n", line3);

	line4 = get_next_line(fd);
	printf("GET4:  %s\n", line4);

	line5 = get_next_line(fd);
	printf("GET5:  %s\n\n", line5);
	free(line1);
	free(line2);
	free(line3);
	free(line4);
	free(line5);
}