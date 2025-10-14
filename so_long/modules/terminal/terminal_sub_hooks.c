/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_sub_hooks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:15:54 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 07:07:10 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	key_erase(t_all *all, int line, int *index)
{
	if (*index > all->terminal->pc_nb_size)
	{
		all->terminal->writed[line][*index] = '\0';
		if (*index > 0)
			(*index)--;
		all->terminal->writed[line][*index] = '_';
		mlx_put_image_to_window(all->mlx, all->window_terminal,
			all->images->blank_letter->st, 10 + ((*index) * 6), 142);
		mlx_string_put(all->mlx, all->window_terminal, 10, 160, 16711680,
			all->terminal->writed[line]);
	}
}

void	key_switch_strings(t_all *all, int keycode, int line, int *focused)
{
	int	*swift_state;

	swift_state = &all->states->swifting_strings;
	if (*swift_state == 0 && keycode == 65362 && (*focused) > 5)
		save_current_string(all, keycode, line);
	if ((keycode == 65362) && ((*focused) > 5) && *swift_state == 1)
	{
		if ((--(*focused)) == line && ((*focused) > 5))
			(*focused)--;
		while ((all->terminal->writed[*focused][0] != 'c') && ((*focused) > 5)
			&& (all->terminal->writed[*focused][0] != 'r'))
			(*focused)--;
	}
	else if ((keycode == 65364) && (*focused < (line + 1)) && *swift_state == 1)
	{
		if ((++(*focused)) == line && (*focused) < (line + 1))
			(*focused)++;
		while ((all->terminal->writed[*focused][0] != 'c') && *focused < line
			&& (all->terminal->writed[*focused][0] != 'r'))
			(*focused)++;
	}
	put_string_focused(all, line, *focused);
}
