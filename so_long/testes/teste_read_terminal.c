/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_read_terminal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 18:23:10 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/24 18:25:47 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	char string[10000];
	int a = read(0, string, 20);
	printf("\n\n\nYou wrote: %s\n", string);
	printf("You wrote: %s\n", string);
	printf("You wrote: %s\n", string);
	printf("You wrote: %s\n", string);
	printf("You wrote: %s\n", string);
	printf("You wrote: %s\n", string);
}