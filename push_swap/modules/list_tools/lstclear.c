/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:04:36 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:31:46 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"

void	lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*nexttemp;

	temp = *lst;
	while (temp != NULL)
	{
		nexttemp = temp->next;
		free(temp);
		temp = nexttemp;
	}
	*lst = NULL;
}

// static void	del(void *content)
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
// 	ft_lstadd_back(&head, node2); // Adds the nodes
// 	ft_lstadd_back(&head, node3); // Adds the nodes
// 	ft_lstadd_back(&head, node4); // Adds the nodes
// 	while (head != NULL)
// 	{
// 		printf("Before: %s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	printf("\n");
// 	lstclear(&node3); // lstclear's the list on "Node3"
// 	while (head2 != NULL)
// 	{
// 		printf("After: %s\n", (char *)head2->content);
// 		head2 = head2->next;
// 	}
// }