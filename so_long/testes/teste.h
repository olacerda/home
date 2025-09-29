/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:00:15 by olacerda          #+#    #+#             */
/*   Updated: 2025/09/12 11:03:09 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TESTE_H
# define TESTE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define BUFFER_SIZE 42

typedef struct s_teste
{
	char buff[BUFFER_SIZE];
	int	start;
	int	end;
	int readbytes;
} t_teste;

#endif