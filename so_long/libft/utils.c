/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 00:37:53 by otlacerd          #+#    #+#             */
/*   Updated: 2025/09/18 10:27:34 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

int	strlength(char *string)
{
	int	length;

	if (!string)
		return (0);
	length = 0;
	while(string[length] != '\0' && string[length] != '\n')
		length++;
	return (length);
}

void	putnumber(int nbr)
{
	if (nbr > 9)
		putnumber(nbr / 10);
	write(1, &"0123456789"[nbr % 10], 1);
}
