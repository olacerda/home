/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:34:20 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 02:23:21 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"

// void	del(int content)
// {
// 	if (!content)
// 		return ;
// 	free(content);
// }



// int	main(void)
// {
// 	t_list	*node1 = lstnew(ft_strdup("Node1"));
// 	t_list	*node2 = lstnew(ft_strdup("Node2"));
// 	t_list	*node3 = lstnew(ft_strdup("Node3"));
// 	t_list	*node4 = lstnew(ft_strdup("Node4"));
	
// 	t_list	*head = node1;
// 	t_list	*head2 = node1;

// 	lstadd_back(&head, node2); // Adds the nodes
// 	lstadd_back(&head, node3); // Adds the nodes
// 	lstadd_back(&head, node4); // Adds the nodes
	
// 	while (head != NULL)
// 	{
// 		printf("Before: %s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	printf("\n");
	
// 	lstclear(&node3, del); // lstclear's the list on "Node3"
		
// 	while (head2 != NULL)
// 	{
// 		printf("After: %s\n", (char *)head2->content);
// 		head2 = head2->next;
// 	}
// }