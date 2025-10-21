/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:29:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:27:10 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "../../push_swap.h"
# include "../list_tools/list_tools.h"

t_stackinfo	*init_struct(void);
void		end_data(t_stackinfo *stack);
void		put_error(t_stackinfo *stack);

#endif