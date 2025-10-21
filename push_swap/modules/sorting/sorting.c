/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:48:36 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:33:32 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sorting.h"

int	get_max_bit_len(t_list *head)
{
	int	result;
	int	comparison;
	int	int_limit;
	int	count;
	int	bit;

	count = 0;
	bit = 0;
	int_limit = (sizeof(int) * 8);
	result = 0;
	while (head != NULL)
	{
		comparison = head->index;
		count = 0;
		while ((count < int_limit) && (((comparison << count)
					& -2147483648) == 0))
			count++;
		bit = int_limit - count;
		if (bit > result)
			result = bit;
		head = head->next;
	}
	return (result);
}

void	sort_contents(t_stackinfo *stack)
{
	int	count;
	int	bit_count;
	int	max_bit_len;

	bit_count = 0;
	max_bit_len = get_max_bit_len(stack->head_a);
	while (bit_count < max_bit_len)
	{
		count = 0;
		while (count < stack->size)
		{
			if (((stack->head_a->index & (1 << bit_count)) == 0))
			{
				pb(&stack->head_a, &stack->head_b);
			}
			else
				ra(&stack->head_a, &stack->tail_a);
			count++;
		}
		while (stack->head_b != NULL)
		{
			pa(&stack->head_a, &stack->head_b);
		}
		bit_count++;
	}
}

// //                     MAIN ---> GET_MAX_BIT_LEN
// // compile with the flag
// // cc sorting.c ../list_tools/lstnew.c ../list_tools/lstadd_front.c
// int	main(void)
// {
// 	t_list *head = lstnew(15);
// 	lstadd_front(&head, lstnew(19));
// 	lstadd_front(&head, lstnew(1));
// 	lstadd_front(&head, lstnew(0));
// 	lstadd_front(&head, lstnew(-2147483648));
// 	int result = get_max_bit_len(head);

// 	printf("result: %d\n\n", result);
// }