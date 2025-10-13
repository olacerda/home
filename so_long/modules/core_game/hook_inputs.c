/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:14:41 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 16:56:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core_game.h"

void	check_key_ender_and_esc(int code, t_all *all)
{
	if (code == 65293)
	{
		all->states->key_enter = 1;
		check_player_range(all, '0');
	}
	if (code == 65307)
		end_game(all);
}

int	check_key_pressed(int	code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	if (code == 100)
	{
		all->states->key_d = 1;
		all->play->direction = 1;
	}
	if (code == 97)
	{
		all->states->key_a = 1;
		all->play->direction = 0;
	}
	if (code == 119)
		all->states->key_w = 1;
	if (code == 115)
		all->states->key_s = 1;
	if (code == 65506)
		all->states->key_shift = 1;
	check_key_ender_and_esc(code, all);
	return (0);
}

int	check_key_released(int code, void *arg)
{
	t_all	*all;

	all = (t_all *)arg;
	if (code == 100)
		all->states->key_d = 0;
	if (code == 97)
		all->states->key_a = 0;
	if (code == 119)
		all->states->key_w = 0;
	if (code == 115)
		all->states->key_s = 0;
	if (code == 65506)
		all->states->key_shift = 0;
	if (code == 65293)
	{
		all->states->key_enter = 0;
	}
	return (0);
}