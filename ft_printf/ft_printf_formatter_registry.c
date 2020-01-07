/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formatter_registry.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 10:34:34 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/27 10:34:34 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*g_formatter_key = FT_PRINTF_SUPPORTED_TYPES;
char	*(*g_formatters[10])(t_ft_printf_bundle *) = {
	&ft_printf_formatter_char,
	&ft_printf_formatter_string,
	&ft_printf_formatter_pointer,
	&ft_printf_formatter_decimal,
	&ft_printf_formatter_decimal,
	&ft_printf_formatter_uint,
	&ft_printf_formatter_hex_int,
	&ft_printf_formatter_hex_int,
	&ft_printf_formatter_pourcent,
	&ft_printf_formatter_octal_int
};

void
	*ft_printf_formatter_get(char key)
{
	size_t			index;

	index = 0;
	while (g_formatter_key[index])
	{
		if (g_formatter_key[index] == key)
			return (g_formatters[index]);
		index++;
	}
	return (NULL);
}
