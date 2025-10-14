/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:16:21 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 06:57:33 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

void	error_message(t_all *all, int *line, char (*writed)[33], int flag)
{
	char	*reference;

	if (flag == 1)
		reference = " ...Program is finished...";
	if (flag == 2)
		reference = "Heap Overflow! Aborted.";
	if (flag == 3)
		reference = "  Pc limit: 5 bytes";
	if (flag == 4)
		reference = " ERROR: Allocation in course";
	if (flag == 5)
		reference = "ERROR: No memory allocated";
	(*line)++;
	all->terminal->wr_index = -1;
	while (reference[++(all->terminal->wr_index)])
		writed[*line][all->terminal->wr_index] = reference[
			all->terminal->wr_index];
	writed[*line][all->terminal->wr_index++] = '\0';
}

void	free_memory(t_all *all)
{
	all->states->allocation = 0;
	rebuild_current_map(all);
	all->play->lttrs_cnt = 0;
	all->play->letter_colected[0] = '\0';
	all->game->memory = 0;
	all->game->shadow = 0;
	if (all->states->root_speed == 0)
		all->game->usleep = 20000;
	all->game->speed = 2;
	all->game->speed2 = 1;
	all->states->undefined_behavior = 0;
	all->play->f = 0;
	all->play->i = 0;
	all->play->r = 0;
	all->play->a = 0;
	all->game->ub_current_time = all->game->ub_time + 1;
	sheet_to_image(all->images->terminal_sheet, all->images->y,
		all->images->grass, 0);
	all->images->background->img = all->images->grass->img;
	update_bg(all->images->player_sheet, all->images->background, all,
		all->play->frame);
	mlx_put_image_to_window(all->mlx, all->window, all->images->y->st,
		all->game->element[indexor("y")].px_column,
		all->game->element[indexor("y")].px_line);
	mlx_do_sync(all->mlx);
}

void	message_clear(t_all *all)
{
	all->terminal->wr_index = 0;
	all->terminal->writed[all->terminal->wr_line][0] = '\0';
	all->terminal->wr_line = 5;
	all->terminal->string_focused = all->terminal->wr_line;
}

int	message_size(t_all *all, char *string)
{
	int	index;
	int	size;

	size = 0;
	index = (all->terminal->pc_nb_size);
	while (string[index] && string[index] != '_')
	{
		index++;
		size++;
	}
	return (size);
}
