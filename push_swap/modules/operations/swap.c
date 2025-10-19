/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:56:02 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/19 05:28:03 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operations.h"

void	swap(t_list *head)
{
	int	temp_content;

	if (!head || !head->next)
		return ;
	temp_content = head->content;
	head->content = head->next->content;
	head->next->content = temp_content;
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