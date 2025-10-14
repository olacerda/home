/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_messages.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:16:03 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 06:58:09 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	message_free(t_all *all, int *line, char (*writed)[33])
{
	if (cmp_msg(all, "free(memory)", writed[*line], 12) == 0)
	{
		if (((all->states->allocation >= 1)
				|| all->states->undefined_behavior > 0))
			free_memory(all);
		else if (all->states->allocation == 0)
			error_message(all, line, writed, 5);
		update_step_and_memory(all, 1);
	}
}

void	message_malloc(t_all *all, int *line, char (*writed)[33], int size)
{
	if (size == 18 || size == 19)
	{
		if (((writed[*line][all->terminal->pc_nb_size + 16] - 48) <= 5)
			&& ((writed[*line][all->terminal->pc_nb_size + 17] <= 47 && writed[
				*line][all->terminal->pc_nb_size + 17] >= 58)
					&& all->states->allocation == 0))
		{
			all->states->allocation = 1;
			all->game->memory = writed[*line][all->terminal->pc_nb_size + 16]
				- 48;
			if (all->play->lttrs_cnt > all->game->memory
				&& all->states->ub_count)
				all->states->undefined_behavior = 1;
		}
		else if (all->states->allocation >= 1)
			error_message(all, line, writed, 4);
		else
		{
			error_message(all, line, writed, 2);
			error_message(all, line, writed, 3);
		}
	}
}

void	message_ls(t_all *all, int *line, char (*writed)[33])
{
	char	*to_write;
	int		*index;

	to_write = NULL;
	index = &all->terminal->wr_index;
	if (cmp_msg(all, "ls", writed[*line], 2) == 0)
	{
		*index = '\0';
		(*line)++;
		(*index) = 0;
		if (all->states->letters_compiled == 0)
			to_write = "  readme   letters.c";
		else
			to_write = "  readme   letters.c   a.out";
		while (to_write[(*index)])
		{
			writed[*line][(*index)] = to_write[(*index)];
			(*index)++;
		}
		writed[*line][(*index)] = '\0';
	}
}

void	cat_a_out(int *line, char (*writed)[33], int *wr_index)
{
	int		size;
	int		index;
	char	*reference1;
	char	*reference2;
	char	*to_write;

	reference1 = "10101010101010101010101010";
	reference2 = "01010101010101010101010101";
	to_write = reference1;
	size = 5;
	++(*line);
	while (size-- > 0)
	{
		if (to_write[0] == '0')
			to_write = reference2;
		else
			to_write = reference1;
		index = -1;
		while (to_write[++index])
			writed[*line][index] = to_write[index];
		writed[*line][index] = '\0';
		if (size != 0)
			(*line)++;
	}
	*wr_index = index;
}
