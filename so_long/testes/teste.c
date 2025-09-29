/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:45:30 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/12 12:12:03 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "teste.h"
#include "so_long.h"

char	*getnextline(int fd)
{
	static t_teste x = {0, BUFFER_SIZE, 0, BUFFER_SIZE};
	int	totalbytes;
	char *line;
	char *newline;
	int	index;

	if (fd < 0 || BUFFER_SIZE <= 0 || x.readbytes < 0)
		return (NULL);
	totalbytes = 0;
	line = NULL;
	if ((x.start >= x.readbytes) || x.readbytes <= 0)
		x = (t_teste){0, BUFFER_SIZE, 0, BUFFER_SIZE};
	while (((x.buff[x.end] != '\n') || line == NULL) && (x.readbytes > 0))
	{
		if (x.start >= x.readbytes)
			x = (t_teste){0, 0, 0, read(fd, x.buff, BUFFER_SIZE)};
		if (x.readbytes <= 0)
			break ;
		while ((x.buff[x.end] != '\n') && (x.end < x.readbytes) && (++x.end))
			totalbytes++;
		newline = malloc((totalbytes + 1 + (x.buff[x.end] == '\n')) * sizeof(char));
		if (!newline)
			return (NULL);
		index = -1;
		while (++index < (totalbytes - x.end) && (line))
			newline[index] = line[index];
		while (x.start <= x.end && (x.start < x.readbytes))
			newline[++index] = x.buff[++x.start];
		newline[index] = '\0';
		free(line);
		line = newline;
	}
	return (x.end += (x.buff[x.end] == '\n'), line);
}

int	main(void)
{
	t_image *image;
	t_sheet *sheet;
	int	size;
	char	*line;

	size = sizeof(*image);
	// printf("%d\n", size);
	size = (sizeof(*sheet));
	// printf("%d\n", size);
	line = "";
	while (line != NULL)
	{
		line = getnextline(0);
		if (line != NULL)
			printf("You wrote: %s", line);
		free (line);
	}
	printf("\n");
}