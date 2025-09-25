/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gustavo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:09:38 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/19 23:38:09 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	putstring(char *string)
{
	int	i = -1;

	while (string[++i] != 0)
		write(1, &string[i], 1);
	write(1, "\n", 1);
}

int	main(void)
{
	putstring("teste oi");
}