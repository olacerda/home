/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:27:59 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/13 21:29:35 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "so_long.h"

void	init_structures(t_all *all);
void	free_structures(t_all *all);
int		end_game(t_all *all);

void	free_map(char **game);
void	destroy_all_images1(void *mlx, t_all_images *images);
void	destroy_all_images2(void *mlx, t_all_images *images);
void	free_all_images1(t_all_images *images);
void	free_all_images2(t_all_images *images);

#endif
