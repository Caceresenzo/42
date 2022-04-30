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
#include <stdlib.h>

#include "nm.h"

t_symbol*
symbol_create(t_elf_address address, bool has_address, const char *name, char letter)
{
	t_symbol *symbol = malloc(sizeof(t_symbol));
	if (symbol)
	{
		symbol->address = address;
		symbol->has_address = has_address;
		symbol->letter = letter;
		symbol->name = name;
	}

	return (symbol);
}

static void
symbol_print(int size, t_symbol *symbol)
{
	if (symbol->has_address)
		printf("%0*lx %c %s\n", size, (long)symbol->address, symbol->letter, symbol->name);
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
symbol_compare(t_symbol *left, t_symbol *right)
{
	int diff = symbol_compare_by_name(left, right);
	if (diff)
		return (diff);

	return (symbol_compare_by_address(left, right));
}

int
symbol_compare_by_name(t_symbol *left, t_symbol *right)
{
	if (left->name == right->name)
		return (0);

	if (left->name && !right->name)
		return (1);

	if (!left->name && right->name)
		return (-1);

	return (strcmp(left->name, right->name));
}

int
symbol_compare_by_address(t_symbol *left, t_symbol *right)
{
	if (left->address > right->address)
		return (1);

	if (left->address < right->address)
		return (-1);

	return (0);
}

