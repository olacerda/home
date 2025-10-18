/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:51:07 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 00:43:59 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"
t_list	*lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// int	main(void)
// {
// 	t_list	*node1 = ft_lstnew("node1");
// 	t_list	*node2 = ft_lstnew("node2");
// 	t_list	*head = node2;
	
// 	char	*result = ft_lstlast(node1)->content;
// 	printf("Last node: %s\n", result);
	
// 	ft_lstadd_front(&head, node1); //add`s node1 in front of node2
	
// 	result = ft_lstlast(node1)->content;
// 	printf("Last node: %s\n", result);	
// }