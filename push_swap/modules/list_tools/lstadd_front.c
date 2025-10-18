/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:17:30 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 00:43:59 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"
void	lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list	*node1 = ft_lstnew("node1");
// 	t_list	*node2 = ft_lstnew("node2");

// 	printf("Primeiro node: %s\n", (char *)node1->content);
// 	ft_lstadd_front(&node1, node2);
// 	printf("Primeiro node: %s\n", (char *)node1->content);
// }