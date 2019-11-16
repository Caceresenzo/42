/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_uint.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:10:22 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 16:10:22 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_f_uint(t_ft_printf_settings *settings,
							t_ft_printf_flags *flags, size_t *index)
{
	unsigned int	decimal;

	FAKE_USE(flags);
	FAKE_USE(index);
	decimal = va_arg(settings->parameters, unsigned int);
	if (ft_printf_f_decimal_should_be_empty(decimal == 0, flags))
		return (ft_emptystr());
	return (ft_itoa_base(decimal, BASE_DECIMAL));
}
