/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 04:29:04 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 11:11:02 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

void	push(t_list **head1, t_list **head2)
{
	t_list	*temp_list;

	if (!(*head2))
		return ;
	temp_list = (*head2);
	(*head2) = (*head2)->next;
	temp_list->next = (*head1);
	(*head1) = temp_list;
}

void	pa(t_list **head1, t_list **head2)
{
	if (!(*head2))
		return ;
	push(head1, head2);
	write(1, "pa\n", 3);
}

void	pb(t_list **head1, t_list **head2)
{
	if (!(*head1))
		return ;
	push(head2, head1);
	write(1, "pb\n", 3);
}
