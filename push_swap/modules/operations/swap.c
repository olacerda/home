/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:56:02 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 11:09:23 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

void	swap(t_list *head)
{
	int	temp_content;
	int	temp_index;

	if (!head || !head->next)
		return ;
	temp_content = head->content;
	temp_index = head->index;
	head->content = head->next->content;
	head->index = head->next->index;
	head->next->content = temp_content;
	head->next->index = temp_index;
}

void	sa(t_list *head)
{
	swap(head);
	write(1, "sa\n", 3);
}

void	sb(t_list *head)
{
	swap(head);
	write(1, "sb\n", 3);
}

void	ss(t_list *head1, t_list *head2)
{
	swap(head1);
	swap(head2);
	write(1, "ss\n", 3);
}
