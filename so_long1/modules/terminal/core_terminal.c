/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:14:54 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 10:58:32 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "terminal.h"

void open_terminal(t_all *all)
{
	char *username;

	username = all->terminal->user_name;
    if (!all->window_terminal)
    {
		all->window_terminal = mlx_new_window(all->mlx, 200, 150, username);
		mlx_hook(all->window_terminal, 2, 1L<<0, new_window_key_pressed, all);
		mlx_hook(all->window_terminal, 3, 1L<<1, new_window_key_released, all);
		if (all->terminal->wr_index == 0)
		{
			put_pcnumber_on_terminal(all, all->terminal->wr_line);
			mlx_string_put(all->mlx, all->window_terminal, 10, 140, 16711680, 
				all->terminal->writed[all->terminal->wr_line]);
		}	
    }
}

int new_window_key_pressed(int code, void *arg)
{
	t_all *all;

	all = (t_all *)arg;
	if (code == 65505 || code == 65506)
		all->states->key_shift = 1;
	if (code == 65507 || code == 65508)
		all->states->key_ctrl = 1;
	if (code == 57 || code == 48)
		key_shift(all, code, all->terminal->wr_line, 
			&all->terminal->wr_index);
	if ((code >= 0 && code <= 25) || (code >= 97 && code <= 122) || code == 47 
		|| code == 61 || code == 32 || code == 46 || (code >= 48 && code <= 57))
		key_alpha_number(all, code);
	else if ((code == 65362) || (code == 65364))
		key_switch_strings(all, code, all->terminal->wr_line, 
			&all->terminal->string_focused);
	else if (code == 65288 || code == 65307)
		key_erase(all, all->terminal->wr_line, &all->terminal->wr_index);
    else if (code == 65293)
		key_enter(all, &all->terminal->wr_line, &all->terminal->wr_index);
	if (all->states->key_ctrl == 1 && code == 99)
		key_ctrl_c(all);
	if (code == 65307)
		end_game(all);
    return 0;
}

int new_window_key_released(int keycode, void *arg)
{
	t_all *all;

	all = (t_all *)arg;
	if (keycode == 65505 || keycode == 65506)
		all->states->key_shift = 0;
	if (keycode == 65507 || keycode == 65508)
		all->states->key_ctrl = 0;
	return (0);
}

int	cmp_msg(t_all * all, char *string1, char *string2, int limit)
{
	int	index1;
	int	index2;
	index1 = 0;
	index2 = all->terminal->pc_nb_size;
	while(string2[index2] != '_' && string1[index1] && string2[index2] && 
		string1[index1] == string2[index2] && limit > 0)
	{
		index1++;
		index2++;
		limit--;
	}
	if (string2[index2] == '_' || (string2[index2] == '\0') || 
		(string2[index2] >= 48 && string2[index2] <= 57))
		{
			index2--;
		}
	if (index1 > 0 && string1[index1] == '\0')
		index1--;
	return (string1[index1] - string2[index2]);
}

void	check_message(t_all *all, int *line, char (*writed)[33], int size)
{
	if ((size == 2) && (cmp_msg(all, "su", writed[*line], 2) == 0))
		message_su(all);
	else if (size == 2)
		message_ls(all, line, writed);
	else if ((size == 3) && (cmp_msg(all, "won", writed[*line], 3) == 0))
		message_won(all);
	else if ((size == 4) && (cmp_msg(all, "exit", writed[*line], 4) == 0))
		message_exit(all);
	else if ((size == 7) && (all->states->letters_compiled == 1) && 
		(cmp_msg(all, "./a.out", writed[*line], 7) == 0))
		put_letter(all, "FIRA", writed, all->game->element);
	else if ((cmp_msg(all, "memory = malloc(", writed[*line], 16) == 0))
		message_malloc(all, line, writed, size);
	else if ((size == 9) && (cmp_msg(all, "speed = ", writed[*line], 8) == 0))
		message_speed(all, (writed[*line][all->terminal->pc_nb_size + 8] - 48));
	else if (size == 12 && cmp_msg(all, "cc letters.c", writed[*line], 12) == 0)
		all->states->letters_compiled = 1;
	else if (size == 12)
		message_free(all, line, writed);
	else if (size == 13 || size == 10 || size == 9 || size == 5)
		message_cat_n_clear(all, line, writed, size);
	if (((size == 16) || (size == 13)) && all->states->root == 1)
		message_able_desabe_ub_count(all, line, writed);
	else if (((size == 10) || (size == 7)) && all->states->root == 1)
		message_able_desable_ub(all, line, writed);
}
