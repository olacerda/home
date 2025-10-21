/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 05:00:24 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 11:09:12 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

void	rotate(t_list **head, t_list **tail)
{
	t_list	*temp_list;

	if (!(*head) || !(*tail))
		return ;
	temp_list = (*head);
	(*head) = (*head)->next;
	(*tail)->next = temp_list;
	(*tail) = temp_list;
	(*tail)->next = NULL;
}

void	ra(t_list **head, t_list **tail)
{
	rotate(head, tail);
	write(1, "ra\n", 3);
}

void	rb(t_list **head, t_list **tail)
{
	rotate(head, tail);
	write(1, "rb\n", 3);
}

void	rr(t_list **head1, t_list **tail1, t_list **head2, t_list **tail2)
{
	rotate(head1, tail1);
	rotate(head2, tail2);
	write(1, "rr\n", 3);
}
