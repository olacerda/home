/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olacerda <olacerda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 04:28:20 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/02 04:37:10 by olacerda         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct timeval t_time;

long	get_full_time()
{
	t_time	time;
	long	now;

	gettimeofday(&time, NULL);
	now = (time.tv_sec * 1000000) + time.tv_usec;
	return (now);
}
int	main(void)
{
	static long time;
	static long last = 0;
	while (1)
	{
		time = get_full_time();
		if (time - last > 200000)
		{
			write(1, "\a", 1);
			last = time;
		}	
	}
}