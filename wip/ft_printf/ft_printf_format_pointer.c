/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_pointer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:44:07 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 14:44:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*internal_ft_printf_f_pointer_precision(t_ft_printf_flags *flags,
													char *ptr_str)
{
	char	*str;
	int		length;

	length = 0;
	if (flags->width_enabled && flags->padding_char == '0')
		length = flags->width - 2;
	if (flags->precision_enabled)
		length = flags->precision;
	str = ft_charmult('0', ZERO_IF_NEG((int)(length - ft_strlen(ptr_str))));
	return (str);
}

char		*ft_printf_f_pointer(t_ft_printf_settings *settings,
							t_ft_printf_flags *flags, size_t *index)
{
	long	ptr;
	char	*str;
	char	*precision;
	char	*joined;
	char	*final;

	FAKE_USE(index);
	ptr = va_arg(settings->parameters, long);
	str = ft_itoa_base(ptr, BASE_HEX_LOW);
	precision = internal_ft_printf_f_pointer_precision(flags, str);
	joined = ft_strjoin(precision, str);
	final = ft_strjoin("0x", ptr == 0 && flags->precision_enabled &&
						flags->precision == 0 ? "" : joined);
	free(str);
	free(precision);
	free(joined);
	return (final);
}
