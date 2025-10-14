/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 22:04:33 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/14 06:12:23 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "modules/data/data.h"
#include "modules/core_game/core_game.h"
#include "modules/parsing/parsing.h"

int	main(int argc, char *argv[])
{
	t_all	*all;

	if (argc != 2)
	{
		write(2, "Error\nIncorret amount of arguments!\n", 36);
		return (1);
	}
	all = malloc(sizeof(t_all));
	if (!all)
	{
		write(2, "Error\nFailed struct \"ALL\" allocation\n", 37);
		return (1);
	}
	init_structures(all);
	general_settings(all);
	if (!(parcing(argv[1], all)))
	{
		write(2, "Error\nFailed due to wrong parsing\n\n\n\n", 37);
		end_game(all);
	}
	game_initializer(all);
	return (0);
}

// COMANDO PRA PEGAR O USER DA PESSOA e colocar num novo arquivo local
// name=$(ls -l | awk '{print $3}' | tail -1)
// &&echo $name >>./ maps / user_name.ber

		// COMANDO PRA PEGAR O COMPUTADOR DA PESSOA e colocar num novo 
		// arquivo local
		// echo $HOST | cut -d'.' -f1 > ./maps/computer_number.ber

		// compilar com
		// cc -Wall -Wextra -Werror -I libft
		// - I MiniLibX / minilibx - linux so_long.c libft / parcing.c libft
		// 	/ utils.c libft / getnextline.c - L MiniLibX / minilibx - linux
		// 	- lmlx - lXext - lX11 - lm


// COMANDO PRA PEGAR O USER DA PESSOA e colocar num novo arquivo local
// name=$(ls -l | awk '{print $3}' | tail -1) && echo $name >> ./maps/user_name.ber

// COMANDO PRA PEGAR O COMPUTADOR DA PESSOA e colocar num novo arquivo local
// echo $HOST | cut -d'.' -f1 > ./maps/computer_number.ber
