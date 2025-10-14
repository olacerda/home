/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:15:43 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 10:58:32 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "terminal.h"

void	key_alpha_number(t_all *all, int keycode)
{
	char (*writed)[33];
	int	line;
	int *index;
	void	*img;
	void	*window;

	writed = all->terminal->writed;
	line = all->terminal->wr_line;
	index = &all->terminal->wr_index;
	img = all->images->blank_letter->st;
	window = all->window_terminal;
	if ((*index < 28) && (all->states->key_shift == 0) 
		&& (all->states->key_ctrl == 0))
	{
		writed[line][*index] = (char)keycode;
		writed[line][*index + 1] = '_';
		writed[line][*index + 2] = '\0';
		mlx_put_image_to_window(all->mlx, window, img, 10 + (*index * 6), 122);
		mlx_string_put(all->mlx, window, 10, 140, 16711680, writed[line]);
		(*index)++;
		all->states->swifting_strings = 0;
		all->terminal->string_focused = all->terminal->wr_line;
	}
}

void	key_enter(t_all *all, int *line, int *index)
{
	static int size;
	int	save_line;

	size = message_size(all, all->terminal->writed[*line]);
	save_line = *line;
	all->terminal->writed[*line][*index] = '\0';
	check_message(all, line, all->terminal->writed, size);
	if (*line != save_line)
		all->terminal->writed[*line][*index] = '\0';
	all->terminal->writed[*line + 1][*index] = '\0';
	flush_strings_on_terminal(all, *line, all->images->blank_letter->st);
	if (cmp_msg(all, "clear", all->terminal->writed[save_line], 5) != 0)
		(*line)++;
	if (*line >= 499)
		*line = 5;
	all->terminal->string_focused = *line;
	all->terminal->current_line_size = 0;
	*index = 0;
	all->states->swifting_strings = 0;
	if (*index == 0)
	{
		put_pcnumber_on_terminal(all, *line);
		mlx_string_put(all->mlx, all->window_terminal, 10, 20 + (6 * 20), 
			16711680, all->terminal->writed[*line]);
	}
}

void	key_shift(t_all *all, int	code, int line, int *index)
{
	if (all->terminal->wr_index < 27 && all->states->key_shift == 1)
	{
		if (code == 57)
		{
			all->terminal->writed[line][*index] = '(';
			all->terminal->writed[line][*index + 1] = '_';
			all->terminal->writed[line][*index + 2] = '\0';
			mlx_put_image_to_window(all->mlx, all->window_terminal, 
				all->images->blank_letter->st, 10 + ((*index) * 6), 120);
			mlx_string_put(all->mlx, all->window_terminal, 10, 140, 
				16711680, all->terminal->writed[line]);
			(*index)++;
		}
		if (code == 48)
		{
			all->terminal->writed[line][*index] = ')';
			all->terminal->writed[line][*index + 1] = '_';
			all->terminal->writed[line][*index + 2] = '\0';
			mlx_put_image_to_window(all->mlx, all->window_terminal, 
				all->images->blank_letter->st, 11 + ((*index) * 6), 120);
			mlx_string_put(all->mlx, all->window_terminal, 10, 140, 
				16711680, all->terminal->writed[line]);
			(*index)++;
		}
	}
}

void	key_ctrl_c(t_all *all)
{
	all->terminal->wr_index = 0;
	all->states->terminal = 0;
	all->states->key_enter = 0;
	all->states->key_ctrl = 0;
	all->states->key_a = 0;
	all->states->key_d = 0;
	all->states->key_s = 0;
	all->states->key_w = 0;
	all->terminal->wr_line = 5;
	all->terminal->string_focused = all->terminal->wr_line;
	mlx_destroy_window(all->mlx, all->window_terminal);
	usleep(1000);
	all->window_terminal = NULL;
}	