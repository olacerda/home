/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:06:07 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:31:14 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"

int	lstsize(t_list *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

// int	main(void)
// {
// 	t_list	*node1 = ft_lstnew("node1");
// 	t_list	*node2 = ft_lstnew("node2");
// 	t_list	*head = node2;
// 	int	size;

// 	size = ft_lstsize(head);
// 	printf("Before: %d\n", size);
// 	ft_lstadd_front(&head, node1);
// 	size = ft_lstsize(node1);
// 	printf("After: %d\n", size);
// }