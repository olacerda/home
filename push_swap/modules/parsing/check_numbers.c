/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:12:48 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 04:51:13 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_one_number(int *index, char *string, t_stackinfo *stack)
{
	while(((string[*index] >= 9 && string[*index] <= 13)
		|| string[*index] == 32) && string[*index] != '\0')
		(*index)++;
	if (((string[*index] < '+' || string[*index] == ',' || string[*index] > '9')
		|| (string[*index] > '-' && string[*index] < '0')) && string[*index])
		put_error(stack);
	else if (string[*index] == '+' || string[*index] == '-')
	{
		(*index)++;
		if (string[*index] == '\0')
			put_error(stack);
	}
	if (string[*index] == '\0')
		return (0);
	if (string[*index] && (string[*index] >= '0' && string[*index] <= '9'))
	{
		while (string[*index]
			&& (string[*index] >= '0' && string[*index] <= '9'))
			(*index)++;
	}
	if ((string[*index] < '0' || string[*index] > '9') && string[*index] != ' '
		&& string[*index] != '\0')
		put_error(stack);
	return (1);
}

int	check_numbers_in_string(char *string, t_stackinfo *stack)
{
	int	index;
	int	number_count;

	number_count = 0;
	index = 0;
	while (string[index] != '\0')
	{
		number_count += check_one_number(&index, string, stack);
	}
	return (number_count);
}

int	count_numbers(int argc, char *argv[], t_stackinfo *stack)
{
	int	line;
	int numbers_count;
	int	result;

	line = 1;
	numbers_count = 0;
	result = 0;
	while (line < argc)
	{
		if (argv[line][0] == '\0')
		{
			put_error(stack);
		}
		result = check_numbers_in_string(argv[line], stack);
		if (result == 0)
		{
			put_error(stack);
		}
		numbers_count += result;
		line++;
	}
	return (numbers_count);
}

int	check_double_numbers(t_stackinfo *stack)
{
	t_list *temp;
	t_list *iter;
	int		number;

	temp = stack->head;
	while (temp != NULL)
	{
		number = temp->content;
		iter = temp;
		while (iter != NULL)
		{
			iter = iter->next;
			if ((iter != NULL) && (number == iter->content))
			{
				put_error(stack);
			}
		}
		temp = temp->next;
	}
	return (1);
}

// int	main(int argc, char *argv[])
// {
// 	int	number_count;

// 	number_count = count_numbers(argc, argv);
// 	if (number_count == -1)
// 	{
// 		write(2, "Error\n", 7);
// 		return (1);
// 	}
// 	printf("number_count: %d\n", number_count);
// }