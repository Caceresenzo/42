/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:50:35 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/14 18:50:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "nm.h"

int
symbol_list_compare_name(const void *a, const void *b)
{
	const t_symbol *left = *(const t_symbol**)a;
	const t_symbol *right = *(const t_symbol**)b;

	if (right->name == NULL)
		return (left->name != NULL);
	if (left->name == NULL)
		return (-1);
	return (ft_strcmp(left->name, right->name));
}

int
symbol_list_compare_name_reversed(const void *a, const void *b)
{
	return (-symbol_list_compare_name(a, b));
}

static bool
symbol_is_undefined(const t_symbol *symbol)
{
	return (symbol->letter == 'U' || symbol->letter == 'w' || symbol->letter == 'v');
}

int
symbol_list_compare_numeric(const void *a, const void *b)
{
	const t_symbol *left = *(const t_symbol**)a;
	const t_symbol *right = *(const t_symbol**)b;

	if (symbol_is_undefined(left))
	{
		if (!symbol_is_undefined(right))
			return (-1);
	}
	else if (symbol_is_undefined(right))
		return (1);
	else if (left->value != right->value)
	{
		if (left->value < right->value)
			return (-1);
		return (1);
	}

	return (symbol_list_compare_name(a, b));
}

int
symbol_list_compare_numeric_reversed(const void *a, const void *b)
{
	return (-symbol_list_compare_numeric(a, b));
}
