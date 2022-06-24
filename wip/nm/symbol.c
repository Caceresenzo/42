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
