/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:32:04 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/14 05:48:02 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include "so_long.h"
# include "../graphic/graphic.h"
# include "../core_game/core_game.h"

t_image			*sheet_initiator(t_all *all, char *adress, char charr,
					t_element *ele);
t_image			*image_initiator(t_all *all, int size, char charr,
					t_element *elements);
t_all_images	*all_images_initiator(t_all *all);
void			all_sheets_initiator(t_all_images *images, t_all *all);

void			all_images_fill_buffers(t_all_images *images);
void			sheet_to_image(t_image *src, t_image *dst, t_image *background,
					int nbr);
void			color_image(t_image *image, int flag);
t_background	*calculate_vars(t_all *all, t_image *src, t_image *dst,
					int nbr);
void			update_bg(t_image *src, t_image *bg, t_all *all, int nbr);

void			put_images(t_all *all, t_mapinfo *mapst, t_element *ele,
					char **map);
void			put_letter(t_all *all, char *let, char (*writed)[33],
					t_element *elemet);
int				rebuild_current_map(t_all *all);

void			player_animation(t_all *all);
void			exit_animation(t_all *all);
void			update_animation_frames(t_all *all, float reference);

void			update_step_and_memory(t_all *all, int flag);
void			update_memory_display(t_all *all);
void			update_steps_display(t_all *all);
char			*steps_to_string(t_all *all, int steps, int size2, int flag);

#endif
