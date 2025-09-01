/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 12:45:20 by olacerda          #+#    #+#             */
/*   Updated: 2025/08/30 16:35:02 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "temp2.h"

char	*get_next_line(int fd)
{
	static t_g	x;

	x.lin = NULL;
	if ((fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > MAX))
		return (NULL);
	if (x.rb <= 0 || x.st >= x.rb)
		x = (t_g){BUFFER_SIZE, BUFFER_SIZE, NULL, -1, 0, 1, {0}, NULL};
	while ((x.lin == NULL || x.buf[x.en] != 10) && x.rb > 0)
	{
		((x.st >= x.rb)) && (x.rb = read(fd, x.buf, BUFFER_SIZE));
		(x.st >= x.rb) && (*(long *)&(x) = 0);
		while ((x.buf[x.en] != 10) && (x.en < x.rb) && ++(x.en))
			++(x.te);
		x.nl = malloc(x.te + 1 + (x.buf[x.en] == 10) * sizeof(char));
		if (!x.nl)
			return (NULL);
		while (++x.id < (x.te - x.en) && x.lin && x.rb > 0)
			x.nl[x.id] = (x.lin)[x.id];
		while ((x.st <= x.en) && (x.st < x.rb) && x.rb > 0)
			x.nl[x.id++] = x.buf[x.st++];
		x.nl[x.id] = '\0';
		free(x.lin);
		*(t_z *)&(x) = (t_z){x.st, x.en, (void *)((long)x.nl * (x.rb > 0)), -1};
	}
	return (x.en += (x.buf[x.en]) == 10, x.te = 0, x.nl = NULL, x.lin);
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