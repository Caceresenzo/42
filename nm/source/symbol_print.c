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
