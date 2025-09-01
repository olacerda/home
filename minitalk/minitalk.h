/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:54:07 by otlacerd          #+#    #+#             */
/*   Updated: 2025/08/28 15:17:50 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>

void	ft_putnumber(int number);
void	putnbr2(int	nbr);
void	myhandler(int sig);
int		ft_atoi(char *nptr);
int		ft_strlen(char *string);

void	handler(int sig);
void	client(int pid, char *string);
void	sbits(char *string, int charcount, int pid, int killcheck);
void	wbits(int *intcount, unsigned char **string, int *strsize, int sig);

// int		joinsize(int size, char **string);
// char	*ft_stringjoin(int size, char **string);
#endif
