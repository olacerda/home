/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:08:14 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 00:43:59 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*temp;
	void	*tempcontent;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst != NULL)
	{
		tempcontent = f(lst->content);
		temp = ft_lstnew(tempcontent);
		if (!temp)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, temp);
		lst = lst->next;
	}
	return (head);
}

// static void	*uppercaserDEMO(void *str)
// {
// 	char	*string;
// 	int	count;

// 	count = 0;
// 	string = ft_strdup((char *)str);
// 	if (!string)
// 		return (NULL);
// 	while (string[count])
// 	{
// 		if (string[count] >= 97 && string[count] <= 122)
// 			string[count] = string[count] - 32;
// 		count++;
// 	}
// 	return ((void *)string);
// }

// static void	del(void *content)
// {
// 	if (!content)
// 		return ;
// 	free(content);
// }

// int	main(void)
// {
// 	char	content1[] = "Node1";
// 	char	content2[] = "Node2";
// 	char	content3[] = "Node3";
// 	t_list	*node1 = ft_lstnew(content1);
// 	t_list	*node2 = ft_lstnew(content2);
// 	t_list	*node3 = ft_lstnew(content3);
// 	t_list	*head1 = node1;
// 	t_list	*head2 = NULL;

// 	ft_lstadd_back(&head1, node2); // <--- Creates the list
// 	ft_lstadd_back(&head1, node3); // <--- Creates the list
	
// 	while (head1 != NULL)
// 	{
// 		printf("First list: %s\n", (char *)head1->content);
// 		head1 = head1->next;
// 	}
// 	printf("\n");
	
// 	head2 = ft_lstmap(node1, uppercaserDEMO, del); // <--- Creates new list
	
// 	while (head2 != NULL)
// 	{
// 		printf("New List: %s\n", (char *)head2->content);
// 		head2 = head2->next;
// 	}	
// }