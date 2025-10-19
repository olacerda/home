/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:18:05 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 19:25:33 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_TOOLS_H
# define LIST_TOOLS_H

# include "../../push_swap.h"

void	lstadd_back(t_list **lst, t_list *new, t_stackinfo *stack);
void	lstadd_front(t_list **lst, t_list *new);
void	lstclear(t_list **lst);
t_list	*lstnew(int content);
int		lstsize(t_list *lst);


void	del(int content);
// void	lstdelone(t_list *lst, void (*del)(int));
// void	lstiter(t_list *lst, void (*f)(int));
// t_list	*lstlast(t_list *lst);
// t_list	*lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));


#endif