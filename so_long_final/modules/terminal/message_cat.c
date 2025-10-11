/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_cat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:16:13 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 17:08:58 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "terminal.h"

void	message_cat_n_clear(t_all* all, int *line, char (*writed)[28], int size)
{
	if (size == 5 && cmp_msg(all, "clear", writed[*line], 5) == 0)
		message_clear(all);
	else if (cmp_msg(all, "cat letters.c",  writed[*line], 13) == 0)
		cat_letters_c(all, line, writed, "FIRA");
	else if ((all->states->letters_compiled == 1) && cmp_msg(all, "cat a.out",
		 writed[*line], 9) == 0)
		cat_a_out(line, writed, &all->terminal->wr_index);
	else if (cmp_msg(all, "cat readme", writed[*line], 10) == 0)
		cat_readme(all, line, writed);
}

void	cat_readme(t_all *all, int *line, char (*writed)[28])
{
	int count;
	int	index;
	char *reference;

	index = 0;
	count = 3;
	(*line)++;
	while (count > 0)
	{
		if (count == 3)
			reference = "\"memory\" is a char *";
		else if (count == 2)
			reference = "This terminal operates two";
		else if (count == 1)
			reference = "C-functions: malloc, and free.";
		index = -1;
		while (reference[++index])
			writed[*line][index] = reference[index];
		writed[*line][index] = '\0';
		if (count > 1)
			(*line)++;
		count--;
	}
	all->terminal->wr_index = index;
}

void	cat_let_nbr(char (*writed)[28], t_all *all, int *let_idx, char *letters)
{
	int	*wr_idx;
	int *line;

	line = &all->terminal->wr_line;
	wr_idx = &all->terminal->wr_index;
	if (writed[*line][*wr_idx] == '1')
	{
		writed[*line][*wr_idx] = (all->game->element[indexor(&(letters
			[*let_idx]))].charr);
		if (writed[*line][*wr_idx] == 'A')
			writed[*line][*wr_idx] = 'E';
		(*wr_idx)++;
	}
	else if (writed[*line][*wr_idx] == '2')
		itoa_adder(all, writed, &(*wr_idx), all->game->element[indexor
			(&(letters[*let_idx]))].column);
	else if (writed[*line][*wr_idx] == '3')
		itoa_adder(all, writed, &(*wr_idx), all->game->element[indexor
			(&(letters[*let_idx]))].line);
	else
		(*wr_idx)++;
}

void	cat_letters_c(t_all *all, int *line, char (*writed)[28], char *letters)
{
	int	let_idx;
	int str_idx;
	int	*wr_idx;
	char *string;

	string = "   mlx_put_image(\"1\", 2, 3)";
	wr_idx = &all->terminal->wr_index;
	let_idx = -1;
	writed[*line][*wr_idx] = '\0';
	(*line)++;
	while (letters[++let_idx])
	{
		(*wr_idx) = 0;
		str_idx = -1;
		while (string[++str_idx])
		{
			writed[*line][*wr_idx] = string[str_idx];
			cat_let_nbr(writed, all, &let_idx, letters);
		}
		writed[*line][*wr_idx] = '\0';
		if (letters[let_idx + 1])
			(*line)++;
	}
	all->terminal->wr_index = (*wr_idx);
}