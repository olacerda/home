/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:51:48 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/21 10:26:38 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	strlength(char *string)
{
	int	size;

	size = 0;
	while (string[size])
	{
		size++;
	}
	return (size);
}

// strlength
// int	main(void)
// {
// 	char *teste = "oi isso e um teste";
// 	int str_size;

// 	str_size = strlength(teste);
// 	printf("String Size: %d\n", str_size);
// }
