/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 10:03:49 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/27 10:06:15 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>

int	mstrcmp(char *string1, char *string2)
{
	int	index;

	index = 0;
	while(string1[index] && string2[index] && string1[index] == string2[index])
		index++;
	return (string1[index] - string2[index]);
}

int	main(void)
{
	printf("%d\n", mstrcmp("oI tudo bem", "oI tudo bem"));
}