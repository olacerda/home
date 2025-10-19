/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:55:11 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/19 06:00:57 by otlacerd         ###   ########.fr       */
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
	stack->size = check_and_count_numbers(argc, argv, stack);
	printf("number_count: %d\n", stack->size);
	if (stack->size == 0)
	{
		put_error(stack);
	}
	create_stack_list(stack, argv, argc);
	if(!check_double_numbers(stack))
		put_error(stack);
	if (!check_if_its_ordered(stack))
		exit (1);
	assign_stack_index(stack);
	t_list *temp = stack->head_a;
	while (temp != NULL)
	{
		printf("%d\n", temp->content);
		printf("index: %d\n\n", temp->index);
		temp = temp->next;
	}
	
	end_data(stack);
	return (0);
}
