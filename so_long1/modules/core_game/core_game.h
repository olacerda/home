/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_game.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:55:37 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/11 19:54:49 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


#ifndef CORE_GAME_H
# define CORE_GAME_H

# include "so_long.h"

void 			game_initializer(t_all *all);
int				game_loop(void *arg);
void			general_settings(t_all *all);
void			update_images(t_all *all, int prev_px_col, int prev_px_line);

int				check_hitbox(t_all *all, char element);
int				update_hitbox(t_all *all, int line, int column, char element);
int				check_player_range(t_all *all, char element);
void			update_player_range(t_all *all, int line, int column, char terminal);

void			update_game(t_all *all);
void 			update_major_elements(t_all *all, int line, int column);
void			check_letters_colected(t_all *all, char	element, int line, int column);

void			get_username_and_pcnumber(t_all *all, int flag, int fd);
void 			make_sound(long frequency);
long			get_full_time();
int				indexor(char *x);
void			subvert_behavior(t_all *all, int *flag);

void			redefine_behavior(t_all *all);
void			redefine_behavior_directions(t_all *all, long *time, long *last);
void			ub_count(t_all *all);
void			display_ub_count(t_all_images *images, int ub_time, t_all *all);
void			display_indefined_behavior_alert(t_all *all);

void			move_right(t_all *all, int line, int col);
void			move_down(t_all *all, int line, int col);
void			move_left(t_all *all, int line, int col);
void			move_up(t_all *all, int line, int col);
void			move_player(t_all *all);

int				check_key_pressed(int	code, void *arg);
int				check_key_released(int code, void *arg);
void			check_key_ender_and_esc(int code, t_all *all);

#endif