/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 03:28:09 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:33:56 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sorting.h"

void	sort_two(t_stackinfo *stack)
{
	if (stack->head_a->index > stack->head_a->next->index)
		ra(&stack->head_a, &stack->tail_a);
}

void	sort_three(t_stackinfo *stack)
{
	if (stack->head_a->index == 3)
	{
		ra(&stack->head_a, &stack->tail_a);
	}
	else if (stack->head_a->next->index == 3)
		rra(&stack->head_a, &stack->tail_a);
	if (stack->head_a->index > stack->head_a->next->index)
		sa(stack->head_a);
}

void	sort_four(t_stackinfo *stack)
{
	if (stack->head_a->next->index == 4)
		ra(&stack->head_a, &stack->tail_a);
	else if (stack->head_a->next->next->index == 4)
	{
		rra(&stack->head_a, &stack->tail_a);
		rra(&stack->head_a, &stack->tail_a);
	}
	else if (stack->head_a->next->next->next->index == 4)
		rra(&stack->head_a, &stack->tail_a);
	pb(&stack->head_a, &stack->head_b);
	sort_three(stack);
	pa(&stack->head_a, &stack->head_b);
	ra(&stack->head_a, &stack->tail_a);
}

void	sort_five(t_stackinfo *stack)
{
	if (stack->head_a->next->index == 5)
		ra(&stack->head_a, &stack->tail_a);
	else if (stack->head_a->next->next->index == 5)
	{
		ra(&stack->head_a, &stack->tail_a);
		ra(&stack->head_a, &stack->tail_a);
	}
	else if (stack->head_a->next->next->next->index == 5)
	{
		rra(&stack->head_a, &stack->tail_a);
		rra(&stack->head_a, &stack->tail_a);
	}
	else if (stack->head_a->next->next->next->next->index == 5)
		rra(&stack->head_a, &stack->tail_a);
	pb(&stack->head_a, &stack->head_b);
	sort_four(stack);
	pa(&stack->head_a, &stack->head_b);
	ra(&stack->head_a, &stack->tail_a);
}

void	sort_case(t_stackinfo *stack, int stack_case)
{
	if (stack_case == 1)
		exit(1);
	else if (stack_case == 2)
		sort_two(stack);
	else if (stack_case == 3)
		sort_three(stack);
	else if (stack_case == 4)
		sort_four(stack);
	else if (stack_case == 5)
		sort_five(stack);
}
