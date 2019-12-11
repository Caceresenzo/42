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

char
	*ft_printf_formatter_uint(t_ft_printf_bundle *bundle)
{
	unsigned int	decimal;
	char			*itoa;

	decimal = va_arg(bundle->settings->parameters, unsigned int);
	if (ft_printf_f_decimal_should_be_empty(decimal == 0, bundle->flags))
		return (ft_emptystr());
	itoa = ft_itoa_u_base(decimal, BASE_DECIMAL);
	if (itoa && bundle->flags->precision_enabled)
		return (ft_printf_padder_add_number_precision(bundle, itoa, 0, 0));
	return (itoa);
}
