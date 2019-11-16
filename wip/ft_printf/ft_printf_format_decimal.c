/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_decimal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:16:07 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 15:16:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_f_decimal_should_be_empty(int equal_zero,
											t_ft_printf_flags *flags)
{
	return (equal_zero && flags->precision_enabled && flags->precision == 0);
}

char	*ft_printf_f_decimal_with_precision(t_ft_printf_flags *flags,
											int decimal, char *formatted,
											size_t length)
{
	int		required;
	char	*zeros;
	char	*str;

	length = ft_strlen(formatted);
	if (flags->width_enabled && flags->padding_char == '0'
			&& !flags->precision_enabled)
		required = flags->width - (decimal < 0);
	else
		required = flags->precision;
	required -= length;
	required = ZERO_IF_NEG(required);
	if (flags->precision_negative)
		required = 1;
	else
		required += (decimal < 0);
	CHECK_PTR_DEF(zeros = ft_charmult('0', required), formatted);
	str = ft_strjoin(zeros, formatted);
	if (decimal < 0)
		str[0] = '-';
	free(formatted);
	free(zeros);
	return (str);
}

char	*ft_printf_f_decimal(t_ft_printf_settings *settings,
							t_ft_printf_flags *flags, size_t *index)
{
	int		decimal;
	char	*str;
	size_t	length;

	FAKE_USE(flags);
	FAKE_USE(index);
	decimal = va_arg(settings->parameters, int);
	if (ft_printf_f_decimal_should_be_empty(decimal == 0, flags))
		return (ft_emptystr());
	if (decimal == -2147483648)
		str = ft_strdup("2147483648");
	else
		str = ft_itoa(ABS(decimal));
	length = ft_strlen(str);
	str = ft_printf_f_decimal_with_precision(flags, decimal, str, length);
	return (str);
}
