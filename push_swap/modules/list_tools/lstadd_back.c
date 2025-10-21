/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:56:44 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:30:24 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"

void	lstadd_back(t_list **lst, t_list *new, t_stackinfo *stack)
{
	t_list	*temp;

	temp = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->next = NULL;
		stack->tail_a = new;
	}
}

// int	main(void)
// {
// 	t_list	*node1 = ft_lstnew("Node1");
// 	t_list	*node2 = ft_lstnew("Node2");
// 	t_list	*node3 = ft_lstnew("Node3");
// 	t_list	*head = node1;
// 	char	*result;

// 	result = ft_lstlast(head)->content;
// 	printf("Last node: %s\n", result);
// 	ft_lstadd_back(&head, node2);
// 	result = ft_lstlast(head)->content;
// 	printf("Last node: %s\n", result);
// 	ft_lstadd_back(&head, node3);
// 	result = ft_lstlast(head)->content;
// 	printf("Last node: %s\n", result);
// }