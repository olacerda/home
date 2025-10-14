/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:57:49 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/12 10:59:51 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TERMINAL_H
# define TERMINAL_H

# include "so_long.h"

void 			open_terminal(t_all *all);
int 			new_window_key_pressed(int keycode, void *arg);
int				new_window_key_released(int keycode, void *arg);
void			check_message(t_all *all, int *line, char (*writed)[33], int size);
int				cmp_msg(t_all * all, char *string1, char *string2, int limit);

void			key_alpha_number(t_all *all, int keycode);
void			key_enter(t_all *all, int *line, int *index);
void			key_shift(t_all *all, int	code, int line, int *index);
void			key_ctrl_c(t_all *all);

void			key_erase(t_all *all, int line, int *index);
void			key_switch_strings(t_all *all, int keycode, int line, int *focused);

void			message_free(t_all *all, int *line, char (*writed)[33]);
void			message_malloc(t_all *all, int *line, char (*writed)[33], int size);
void			message_ls(t_all *all, int *line, char (*writed)[33]);
void			cat_a_out(int *line, char (*writed)[33], int *wr_index);

void			message_cat_n_clear(t_all* all, int *line, char (*writed)[33], int size);
void			cat_readme(t_all *all, int *line, char (*writed)[33]);
void			cat_letters_c(t_all *all, int *line, char (*writed)[33], char *letters);
void			cat_let_nbr(char (*writed)[33], t_all *all, int *let_idx, char *letters);

void			error_message(t_all *all, int *line, char (*writed)[33], int flag);
void			free_memory(t_all *all);
void			message_clear(t_all *all);
int				message_size(t_all *all, char *string);


void			message_su(t_all *all);
void			message_exit(t_all *all);

void			message_won(t_all *all);
void			message_speed(t_all *all, int speed);
void			message_able_desabe_ub_count(t_all *all, int *line, char (*writed)[33]);
void			message_able_desable_ub(t_all *all, int *line, char (*writed)[33]);

void			itoa_adder(t_all *all, char (*original)[33], int *org_idx, int to_add);
void			put_pcnumber_on_terminal(t_all *all, int line);
void			flush_strings_on_terminal(t_all *all, int line, void *blank);
void			put_string_focused(t_all *all, int line, int focused);
void			save_current_string(t_all *all, int keycode, int line);

#endif