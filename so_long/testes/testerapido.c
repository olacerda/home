/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testerapido.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 21:40:24 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/24 23:47:05 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main()
{
	struct s_tipo {char a, b;} teste = {'a', 'b'};

	(void)teste;
	printf("%li\n", sizeof(struct s_tipo));
	printf("%li\n", sizeof(struct s_tipo *));
}