/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:12:06 by olacerda          #+#    #+#             */
/*   Updated: 2025/10/13 21:59:36 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_map_adrees_need(char *map_name)
{
	int		index;
	int		mp_size;
	char	*comparison;

	mp_size = 0;
	while (map_name[mp_size])
		mp_size++;
	if (mp_size < 10)
		return (1);
	comparison = "maps/";
	index = 0;
	while (index < 5)
	{
		if (comparison[index] != map_name[index])
			return (1);
		index++;
	}
	if (comparison[index] == '\0')
		return (0);
	return (1);
}

char	*get_map_adress(char *map_name, t_all *all)
{
	char	*adress;
	char	*addition;
	int		adr_idx;
	int		index;
	int		name_length;

	if (check_map_adrees_need(map_name) == 0)
		return (map_name);
	name_length = strlength(map_name);
	adress = malloc((name_length + 5 + 1) * sizeof(char));
	if (!adress || !map_name)
	{
		write(2, "Error\nFailed to get map\n", 25);
		end_game(all);
	}
	addition = "maps/";
	index = -1;
	adr_idx = 0;
	while (addition[++index] && (adr_idx < name_length + 5 + 1))
		adress[adr_idx++] = addition[index];
	index = -1;
	while ((map_name[++index] != '\0') && (adr_idx < name_length + 5 + 1))
		adress[adr_idx++] = map_name[index];
	adress[adr_idx] = '\0';
	return (adress);
}

int	check_map_ber_type(char *name)
{
	char	*file_type;
	int		f_index;
	int		index;

	index = 0;
	f_index = -1;
	file_type = ".ber";
	if (!name)
		return (0);
	while (name[index] != '\0')
		index++;
	if (index < 5)
		return (0);
	index -= 4;
	while ((file_type[++f_index] == name[index]) && (file_type[f_index]))
		index++;
	if (file_type[f_index] == '\0')
		return (1);
	return (0);
}
