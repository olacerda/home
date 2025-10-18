/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:55:11 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 04:49:06 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./modules/parsing/parsing.h"
#include "./modules/data/data.h"

int	main(int argc, char *argv[])
{
	t_stackinfo *stack;

	if (argc == 1)
		return (1);
	stack = init_struct();
	stack->size = count_numbers(argc, argv, stack);
	printf("number_count: %d\n", stack->size);
	if (stack->size == 0)
	{
		put_error(stack);
	}
	create_stack_list(stack, argv, argc);
	if(!check_double_numbers(stack))
		put_error(stack);
	while (stack->head != NULL)
	{
		printf("%d\n", stack->head->content);
		stack->head = stack->head->next;
	}
	end_data(stack);
	return (0);
}
