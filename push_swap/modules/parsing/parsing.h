/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:58:28 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:26:35 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../push_swap.h"
# include "../data/data.h"
# include "../list_tools/list_tools.h"

int		check_and_count_numbers(int argc, char *argv[], t_stackinfo *stack);
int		check_numbers_in_string(char *string, t_stackinfo *stack);
int		check_one_number(int *index, char *string, t_stackinfo *stack);

void	create_stack_list(t_stackinfo *stack, char *argv[], int argc);
void	create_1_node_per_nbr(char *string, t_stackinfo *stack, int *index);
int		special_atoi(char *string, int *index, t_stackinfo *stack,
			int negative);
void	assign_stack_index(t_stackinfo *stack);

int		check_double_numbers(t_stackinfo *stack);
int		check_if_its_ordered(t_stackinfo *stack);

int		strlength(char *string);

#endif
