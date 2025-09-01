/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   123.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 19:12:55 by olacerda          #+#    #+#             */
/*   Updated: 2025/08/31 19:41:55 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <unistd.h>
#include <stdio.h>

typedef struct s_mstru
{
	int	a;
	int	b;
} t_mstru;

void teste(void)
{
	t_mstru structure = {10, 10};

	printf("a: %d\nb: %d\n", structure.a, structure.b);	
	*(long *)&structure = 4294967297;
	printf("\n AFTER na casa da joaquina \n\na: %d\nb: %d\n", structure.a, structure.b);	
}

int	main(void)
{
	long	max;
	int	testenbr;

	testenbr = 1 << 31;

	max = 1l << 32;
	max = max + 1;
	teste();
	printf("%d\n", testenbr);
}