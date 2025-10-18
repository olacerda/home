/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:58:28 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 04:45:34 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../push_swap.h"
# include "../data/data.h"
# include "../list_tools/list_tools.h"

int		count_numbers(int argc, char *argv[], t_stackinfo *stack);
int		check_numbers_in_string(char *string, t_stackinfo *stack);
int		check_one_number(int *index, char *string, t_stackinfo *stack);
// void	create_array(t_stackinfo *stack, int argc, char *argv[]);

void	create_stack_list(t_stackinfo *stack, char *argv[], int argc);
void	create_1_node_per_nbr(char *string, t_stackinfo *stack, int *index);
// int 	special_atoi(char *string, int *index, int alter_index);
int		special_atoi(char *string, int *index, t_stackinfo *stack, int negative);

int		check_double_numbers(t_stackinfo *stack);

int		strlength(char *string);


#endif
