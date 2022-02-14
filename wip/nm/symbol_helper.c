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

#include "nm.h"

t_symbol*
symbol_create(t_elf_address address, bool has_address, const char *name, char letter)
{
	t_symbol *symbol = malloc(sizeof(t_symbol));
	if (symbol)
	{
		symbol->address = address;
		symbol->has_address = true;
		symbol->letter = letter;
		symbol->name = name;
	}

	return (symbol);
}

void
symbol_print(t_symbol *symbol)
{
	if (symbol->has_address)
		printf("%016lx %c %s\n", (long)symbol->address, symbol->letter, symbol->name);
	else
		printf("%16s %c %s\n", "", symbol->letter, symbol->name);
}

int
symbol_compare(t_symbol *left, t_symbol *right)
{
	if (left->name == right->name)
		return (0);

	if (left->name && !right->name)
		return (1);

	if (!left->name && right->name)
		return (-1);

	return (strcmp(left->name, right->name));
}
