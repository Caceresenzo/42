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
	{
		char buffer[16 + 1];
		ft_itoa((long)symbol->value, buffer, 16);

		int len = ft_strlen(buffer);
		if (len != size)
		{
			char zeros[16 + 1] = "0000000000000000";
			zeros[size - len] = '\0';
			ft_putstr_fd(zeros, STDOUT_FILENO);
		}

		ft_putstr_fd(buffer, STDOUT_FILENO);
	}
	else
	{
		char spaces[16 + 1] = "                ";
		spaces[size] = '\0';

		ft_putstr_fd(spaces, STDOUT_FILENO);
	}

	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putchar_fd(symbol->letter, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(symbol->name, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
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

static const char*
skip_underscores(const char *str)
{
	while (*str == '_')
		++str;
	return (str);
}

int
symbol_list_compare_name(const void *a, const void *b)
{
	const t_symbol *left = *(const t_symbol**)a;
	const t_symbol *right = *(const t_symbol**)b;

	if (right->name == NULL)
		return (left->name != NULL);
	if (left->name == NULL)
		return (-1);
	return (ft_strcasecmp(skip_underscores(left->name), skip_underscores(right->name)));
}

int
symbol_list_compare_numeric(const void *a, const void *b)
{
	const t_symbol *left = *(const t_symbol**)a;
	const t_symbol *right = *(const t_symbol**)b;

	if (right->value == left->value)
		return (0);
	if (right->value > left->value)
		return (-1);
	return (1);
}
