/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:18:05 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:28:08 by otlacerd         ###   ########.fr       */
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

#endif