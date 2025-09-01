/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maracutaia_initializer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:13:46 by olacerda          #+#    #+#             */
/*   Updated: 2025/08/31 18:20:05 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "getnextline_FINAL.h"

void	testes(void)
{
	t_g x;

	x = (t_g){&(x.nline[x.index] = '\0') - x.index}; // Acrescenta '\0' no final da string e retorna um ponteiro pro início dela,
	x = (t_g){(void *)((long)x.nline * (x.rb > 0))}; // Faz um ponteiro ser NULL ou ele mesmo dependendo de uma condição.
}