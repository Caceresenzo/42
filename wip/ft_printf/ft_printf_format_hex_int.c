/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_hex_int.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:25:15 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 15:25:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*i_ft_printf_f_hex_int(char *converted,
								t_ft_printf_flags *flags, int is_zero)
{
	int		size;
	char	*padding;
	char	*str;
	char	*joined;

	size = 0;
	if (flags->precision_enabled)
	{
		if (!flags->precision_negative)
			size = flags->precision - ft_strlen(converted);
	}
	else if (!flags->side && flags->padding_char == '0')
	{
		size = flags->width - ft_strlen(converted) - (flags->hashtag ? 2 : 0);
	}
	padding = ft_charmult('0', ZERO_IF_NEG(size));
	if (flags->hashtag && !is_zero)
		str = ft_strjoin(flags->hex__upper ? "0X" : "0x", padding);
	else
		str = ft_strjoin("", padding);
	joined = ft_strjoin(str, converted);
	free(padding);
	free(str);
	free(converted);
	return (joined);
}

char		*ft_printf_formatter_hex_int(t_ft_printf_bundle *bundle)
{
	unsigned int	decimal;
	char			*str;

	decimal = va_arg(bundle->settings->parameters, unsigned int);
	bundle->flags->hex__upper = bundle->flags->letter == 'X';
	if (ft_printf_f_decimal_should_be_empty(decimal == 0, bundle->flags))
		return (ft_emptystr());
	str = ft_itoa_base(decimal,
			(bundle->flags->hex__upper ? BASE_HEX_UP : BASE_HEX_LOW));
	str = i_ft_printf_f_hex_int(str, bundle->flags, decimal == 0);
	return (str);
}
