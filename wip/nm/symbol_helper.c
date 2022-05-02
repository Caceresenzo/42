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

t_symbol*
symbol_create(t_elf_address value, bool has_value, const char *name, char letter)
{
	t_symbol *symbol = malloc(sizeof(t_symbol));
	if (symbol)
	{
		symbol->value = value;
		symbol->has_value = has_value;
		symbol->letter = letter;
		symbol->name = name;
	}

	return (symbol);
}

static void
symbol_print(int size, t_symbol *symbol)
{
	if (symbol->has_value)
		printf("%0*lx %c %s\n", size, (long)symbol->value, symbol->letter, symbol->name);
	else
		printf("%*s %c %s\n", size, "", symbol->letter, symbol->name);
}

void
symbol_print_x64(t_symbol *symbol)
{
	return (symbol_print(16, symbol));
}

void
symbol_print_x32(t_symbol *symbol)
{
	return (symbol_print(8, symbol));
}

int
symbol_compare(const t_symbol *left, const t_symbol *right)
{
	if (right->name == NULL)
		return (left->name != NULL);
	if (left->name == NULL)
		return (-1);
	return (strcmp(left->name, right->name));
}

int
symbol_list_compare(const void *a, const void *b)
{
	const t_symbol *left = *(const t_symbol**)a;
	const t_symbol *right = *(const t_symbol**)b;

	return (symbol_compare(left, right));
}

int
symbol_list_compare_reverse(const void *a, const void *b)
{
	return (-symbol_list_compare(a, b));
}
