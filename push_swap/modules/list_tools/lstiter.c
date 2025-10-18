/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstiter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:44:53 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 02:09:37 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"
void	lstiter(t_list *lst, void (*f)(int))
{
	t_list	*head;

	head = lst;
	if (!lst || !f)
		return ;
	while (head != NULL)
	{
		f(head->content);
		head = head->next;
	}
}

// static void	uppercaserDEMO(void *str)
// {
// 	char	*string;
// 	int	count;

// 	string = (char *)str;
// 	count = 0;
// 	while (string[count])
// 	{
// 		if (string[count] >= 97 && string[count] <= 122)
// 			string[count] = string[count] - 32;
// 		count++;
// 	}
// }

// int	main(void)
// {
// 	char	content1[] = "node1";
// 	char	content2[] = "node2";
// 	t_list	*node1 = ft_lstnew(content1);
// 	t_list	*node2 = ft_lstnew(content2);
// 	t_list	*head1 = node1;
// 	t_list	*head2 = node1;

// 	ft_lstadd_back(&head1, node2); // <--- Creates the list adding node2 at final
	
// 	while (head1 != NULL)
// 	{
// 		printf("Before: %s\n", (char *)head1->content);
// 		head1 = head1->next;
// 	}
// 	printf("\n");
	
// 	ft_lstiter(node1, uppercaserDEMO); // <--- Applying the sub-function

// 	while (head2 != NULL)
// 	{
// 		printf("After: %s\n", (char *)head2->content);
// 		head2 = head2->next;
// 	}
// }