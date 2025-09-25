/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste_indexor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:33:14 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/24 17:43:18 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// int	main(void)
// {
// 	struct s_tipo {int a, b, c; char *d, *e;} struct1 = {1, 2, 3, "Teste", "Banana"};
// 	printf("%d\n%d\n%d\n\n", struct1.a, struct1.b, struct1.c);
// 	*(long *)&struct1 = ((48L << 32) + 116);
// 	printf("%d\n%d\n%d\n", struct1.a, struct1.b, struct1.c);
// 	// printf("%li\n", 1l << 32);
// }

int	indexor(char *x)
{
	int	index;
	char *string;

	index = 0;
	if (x[1] != '\0')
		string = x;
	else
		string = "PEC10RXITO";
	while (string[index] != *x && (string[index]))
		index++;
	return (index);
}

int	main(void)
{
	int	teste = indexor("P");
	printf("%d\n", teste);
}