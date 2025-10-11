/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:17:23 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 19:30:02 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "terminal.h"

void	itoa_adder(t_all *all, char (*original)[28], int *org_idx, int to_add)
{
	if (to_add > 9)
	{
		itoa_adder(all, original, org_idx, to_add / 10);
	}
	original[all->terminal->wr_line][(*org_idx)++] = ((to_add % 10) + 48);
}

void	put_pcnumber_on_terminal(t_all *all, int line)
{
	char *user_pc;
	int	*index;

	user_pc = all->terminal->line_start;
	index = &all->terminal->wr_index;
	*index = 0;
	while (user_pc[*index])
	{
		all->terminal->writed[line][*index] = user_pc[*index];
		(*index)++;
	}
	all->terminal->writed[line][(*index)++] = ' ';
	all->terminal->writed[line][*index] = '\0';
}

void	flush_strings_on_terminal(t_all *all, int line, void *blank)
{
	int	count;

	count = 0;
	mlx_put_image_to_window(all->mlx, all->window_terminal, blank, 0, 0);
	while (count < 6)
	{
		mlx_string_put(all->mlx, all->window_terminal, 10, 20 + (count * 20),
			16711680, all->terminal->writed[line - 5 + count]);
		count++;
	}
}

void	put_string_focused(t_all *all, int line, int focused)
{
	char	(*writed)[28];
	int	index;

	writed = all->terminal->writed;
	index = 0;
	while (writed[focused][index] && (index < 27))
	{
		writed[line][index] = writed[focused][index];
		index++;
	}
	if (index > all->terminal->pc_nb_size)
	{
		writed[line][index] = '\0';
		all->terminal->wr_index = index;
	}
	else
	{
		writed[line][all->terminal->pc_nb_size] = '\0';
		all->terminal->wr_index = all->terminal->pc_nb_size;
	}
	mlx_put_image_to_window(all->mlx, all->window_terminal, 
		all->images->blank_letter->st, 0, 130);
	mlx_string_put(all->mlx, all->window_terminal, 10, (7 * 20),
		16711680, writed[line]);
}

void	save_current_string(t_all *all, int keycode, int line)
{
	char (*writed)[28];
	int *line_size;

	writed = all->terminal->writed;
	line_size = &all->terminal->current_line_size;
	if (all->states->swifting_strings == 0 && keycode == 65362 && 
		all->terminal->string_focused > 5)
	{
		while ((writed[line][*line_size] != '_') && writed[line][*line_size])
		{
			writed[line + 1][*line_size] = writed[line][*line_size];
			(*line_size)++;
		}
		all->states->swifting_strings = 1;
	}
}
