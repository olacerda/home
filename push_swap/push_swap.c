/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:55:11 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 11:31:43 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./modules/data/data.h"
#include "./modules/parsing/parsing.h"
#include "./modules/sorting/sorting.h"

int	main(int argc, char *argv[])
{
	t_stackinfo	*stack;

	if (argc == 1)
		return (1);
	stack = init_struct();
	stack->size = check_and_count_numbers(argc, argv, stack);
	if (stack->size == 0)
	{
		end_data(stack);
		exit(1);
	}
	create_stack_list(stack, argv, argc);
	if (!check_double_numbers(stack))
		put_error(stack);
	if (!check_if_its_ordered(stack))
		put_error(stack);
	assign_stack_index(stack);
	if (stack->size <= 5)
		sort_case(stack, stack->size);
	else
		sort_contents(stack);
	end_data(stack);
	return (0);
}
