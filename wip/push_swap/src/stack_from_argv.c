/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_fill_from_argv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:24:34 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 13:24:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>

#include "../libft/libft.h"
#include "../libstack/stack.h"

static bool
	atoi_strict(const char *in, int *out)
{
	long	value;
	int		negativity;
	char	c;

	if (!in || !*in || (*in == '-' && !*(in + 1)))
		return (false);
	value = 0;
	negativity = 1;
	if (*in == '-')
	{
		negativity = -1;
		in++;
	}
	while ((c = *in))
	{
		if (!ft_isdigit(c))
			return (false);
		if (value == INT_MAX || (negativity == -1 && -value == INT_MIN))
			return (false);
		value *= 10;
		value += c - '0';
		in++;
	}
	*out = value * negativity;
	return (true);
}

bool
	stack_fill_from_argv(t_stack *stack, int argc, char **argv)
{
	int index;
	int value;

	index = argc - 1;
	while (index != 0)
	{
		if (!atoi_strict(argv[index], &value))
			return (false);
		if (stack_index_of(stack, value) != -1)
			return (false);
		stack_push(stack, value);
		index--;
	}
	return (true);
}
