/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:14:08 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 19:57:47 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "core_game.h"

int	indexor(char *x)
{
	static int	flag = 1;
	int	index;
	static char *string = 0;

	if (flag == 1)
	{
		string = x;
		flag = 0;
	}
	index = 0;
	while (string[index] != *x && (string[index]))
		index++;
	return (index);
}

void	get_username_and_pcnumber(t_all *all, int size, int fd)
{
	if (size == 0)
	{
		fd = open("../userinfo/user_name.ber", O_RDONLY);
		all->terminal->user_name = getnextline(fd);
		if (fd < 0 || !all->terminal->user_name)
		{
			all->terminal->user_name = "TERMINAL";
			all->states->user_name = 0;
		}
		close(fd);
		fd = open("../userinfo/computer_number.ber", O_RDONLY);
		all->terminal->user_pc_number = getnextline(fd);
		all->states->pc_number = 1;
		if (fd < 0 || !all->terminal->user_pc_number)
		{
			all->terminal->user_pc_number = "comand: ";
			all->states->pc_number = 0;
		}
		close (fd);
		while(all->terminal->user_pc_number[size])
			size++;
	}
	all->terminal->line_start = all->terminal->user_pc_number;
	all->terminal->pc_nb_size = size + 1;
}

void make_sound(long frequency)
{
    static long bell_last = 0;
    long time = get_full_time();

    if (bell_last == 0) 
    {
        bell_last = time;
        write(1, "\a", 1);
        return;
    }

    if (time - bell_last > frequency)
    {
        write(1, "\a", 1);
        bell_last = time;
    }
}

long	get_full_time()
{
	t_time	time;
	long	now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000000) + time.tv_usec;
	return (now);
}

void	subvert_behavior(t_all *all, int *flag)
{
	all->game->usleep = 65000;
	(all->game->speed < 0) && (all->game->speed = -16);
	(all->game->speed > 0) && (all->game->speed = 16);
	if (*flag == 0)
	{
		(all->game->speed2) = -(all->game->speed2);
		*flag = 1;
	}
	if (all->play->letter_colected[all->play->lttrs_cnt - 1])
		all->images->background->img = 
			all->game->element[indexor(&(all->play->letter_colected
				[all->play->lttrs_cnt - 1]))].img;
	else
		all->images->background->img = all->images->grass->img;
}