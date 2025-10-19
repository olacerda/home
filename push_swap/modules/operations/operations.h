/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:00:40 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/19 05:46:31 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

#include "../../push_swap.h"

void	swap(t_list *head);
void	sa(t_list *head);
void	sb(t_list *head);
void	ss(t_list *head1, t_list *head2);

void	push(t_list **head1, t_list **head2);
void	pa(t_list **head1, t_list **head2);
void	pb(t_list **head1, t_list **head2);

void	rotate(t_list **head, t_list **tail);
void	ra(t_list **head, t_list **tail);
void	rb(t_list **head, t_list **tail);
void	rr(t_list **head1, t_list **tail1, t_list **head2, t_list **tail2);

void	reverse_rotate(t_list **head, t_list **tail);
void	rra(t_list **head, t_list **tail);
void	rrb(t_list **head, t_list **tail);
void	rrr(t_list **head1, t_list **tail1, t_list **head2, t_list **tail2);


#endif
