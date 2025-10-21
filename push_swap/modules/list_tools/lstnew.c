/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:43:44 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:31:24 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list_tools.h"

t_list	*lstnew(int content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int	main(void)
// {
// 	t_list	*new = NULL;
// 	char	*content = "Isso e um teste";

// 	if (new == NULL)
// 		printf("Antes: NULL\n");
// 	else
// 		printf("Antes: %s\n", (char *)new->content);
// 	new = ft_lstnew(content);
// 	if (new == NULL)
// 		printf("Antes: NULL");
// 	else
// 		printf("Depois: %s\n", (char *)new->content);
// }
