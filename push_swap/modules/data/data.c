/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 20:30:18 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 02:22:49 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

t_stackinfo	*init_struct(void)
{
	t_stackinfo *stack;

	stack = malloc(sizeof(t_stackinfo));
	if (!stack)
	{
		put_error(stack);
	}
	*stack = (t_stackinfo){0, 0, 0};
	return (stack);
}

void	end_data(t_stackinfo *stack)
{
	if (stack->head)
		lstclear(&stack->head);
	if (stack)
	{
		free(stack);
	}
	exit (1);
}

void	put_error(t_stackinfo *stack)
{
	write(2, "Error\n", 7);
	end_data(stack);
	exit (1);
}

// int	main(void)
// {
// 	t_stackinfo *stack;

// 	stack = init_struct();
// 	printf("size: %d", stack->size);
// 	delete_data(stack);
// }