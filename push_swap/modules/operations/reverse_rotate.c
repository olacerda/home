/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 05:13:35 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 11:09:03 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

void	reverse_rotate(t_list **head, t_list **tail)
{
	t_list	*temp;
	t_list	*pre_tail;

	if (!(*head) || !(*tail))
		return ;
	pre_tail = (*head);
	while (pre_tail->next->next)
		pre_tail = pre_tail->next;
	temp = (*tail);
	(*tail) = pre_tail;
	(*tail)->next = NULL;
	temp->next = (*head);
	(*head) = temp;
}

void	rra(t_list **head, t_list **tail)
{
	reverse_rotate(head, tail);
	write(1, "rra\n", 4);
}

void	rrb(t_list **head, t_list **tail)
{
	reverse_rotate(head, tail);
	write(1, "rrb\n", 4);
}

void	rrr(t_list **head1, t_list **tail1, t_list **head2, t_list **tail2)
{
	reverse_rotate(head1, tail1);
	reverse_rotate(head2, tail2);
	write(1, "rrr\n", 4);
}
