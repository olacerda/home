/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:48:44 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:32:49 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_H
# define SORTING_H

# include "../../push_swap.h"
# include "../data/data.h"
# include "../list_tools/list_tools.h"
# include "../operations/operations.h"

int		get_max_bit_len(t_list *head);
void	sort_contents(t_stackinfo *stack);

void	sort_case(t_stackinfo *stack, int stack_case);
void	sort_five(t_stackinfo *stack);
void	sort_four(t_stackinfo *stack);
void	sort_three(t_stackinfo *stack);
void	sort_two(t_stackinfo *stack);

#endif