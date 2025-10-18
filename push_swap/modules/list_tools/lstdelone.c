/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdelone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 21:02:48 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 02:08:18 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"
void	lstdelone(t_list *lst, void (*del)(int))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

// static void	del(void *content)
// {
// 	if (!content)
// 		return ;
// 	free(content);
// }

// int	main(void)
// {
// 	char	content1[] = "Node1";
// 	t_list	*node1 = ft_lstnew(ft_strdup(content1));
	
// 	printf("Before: %s\n", (char *)node1->content);
		
// 	ft_lstdelone(node1, del); // <--- function lstdelone activated
	
// 	printf("After: %s\n", (char *)node1->content);
// }