/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creating_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:00:47 by otlacerd          #+#    #+#             */
/*   Updated: 2025/10/18 04:38:43 by otlacerd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int special_atoi(char *string, int *index, int alter_index)
// {
// 	static int	result;

// 	if (string[*index] == '\0')
// 		return (result);
// 	if (alter_index == 0)
// 	{
// 		result = 0;
// 		alter_index = *index;
// 	}
// 	if (string[*index] != '\0' || string[*index] != ' ')
// 	{
// 		++(*index);
// 		special_atoi(string, index, alter_index + 1);
// 	}
// 	if (string[alter_index] == '\0' || string[alter_index] == ' ')
// 		alter_index--;
// 	if (string[alter_index] != '\0')
// 		result = result * 10 + string[alter_index] - 48;
// 	return (result);
// }

int	special_atoi(char *string, int *index, t_stackinfo *stack, int negative)
{
	long	result;

	result = 0;
	while ((string[*index]) && (string[*index] >= '0' && string[*index] <= '9'))
	{
		result = (result * 10) + string[*index] - 48;
		(*index)++;
	}
	if (negative == 1)
		result = -result;
	if ((result < (-(1L << 31))) || result > ((1L << 31) - 1))
	{
		put_error(stack);
	}
	return (result);
}

void	create_1_node_per_nbr(char *string, t_stackinfo *stack, int *index)
{
	static int	first = 1;
	int			negative;

	negative = 0;
	while(((string[*index] >= 9 && string[*index] <= 13)
		|| string[*index] == 32) && string[*index])
	{
		(*index)++;
	}
	if ((string[*index]) && (string[*index] == '+' || string[*index] == '-'))
		if (string[(*index)++] == '-')
			negative = 1;
	if (string[*index] && (string[*index] >= '0' && string[*index] <= '9'))
	{
		if (first)
		{
			stack->head = lstnew(special_atoi(string, index, stack, negative));
			stack->head->next = NULL;
			stack->tail = stack->head;
			first = 0;
		}
		else
			lstadd_front(&stack->head, lstnew(special_atoi(string, index, stack,
				negative)));
	}
}

void	create_stack_list(t_stackinfo *stack, char *argv[], int argc)
{
	int	line;
	int	index;

	line = 1;
	while (line < argc)
	{
		index = 0;
		while (argv[line][index])
		{
			create_1_node_per_nbr(argv[line], stack, &index);
		}
		line++;
	}
}

// int	main(int argc, char *argv[])
// {
// 	t_stackinfo *stack;
// 	int	number_count;

// 	stack = init_struct();
// 	number_count = count_numbers(argc, argv, stack);
// 	if (number_count == -1)
// 	{
// 		write(2, "Error\n", 7);
// 		return (1);
// 	}
// 	create_stack_list(stack, argv, argc);
// 	while(stack->head != NULL)
// 	{
// 		printf("%d\n", stack->head->content);
// 		stack->head = stack->head->next;
// 	}
// 	printf("number_count: %d\n", number_count);
// }

//main min max int
// int	main(void)
// {
// 	printf("%d\n\n", (1 << 31));
// 	printf("%li\n", ((1L << 31) - 1));
// }
