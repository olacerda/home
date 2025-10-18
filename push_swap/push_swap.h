/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:55:13 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 00:23:26 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_list
{
	int 			content;
	struct s_list 	*next;
} 				t_list;

typedef struct	s_stackinfo
{
	t_list		*head;
	t_list		*tail;
	int 		size;
}				t_stackinfo;

#endif