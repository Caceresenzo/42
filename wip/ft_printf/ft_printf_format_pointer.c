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

char		*ft_printf_formatter_pointer(t_ft_printf_bundle *bundle)
{
	unsigned long	ptr;
	char			*itoa;
	char			*str;
	char			*final;

	ptr = (unsigned long)va_arg(bundle->settings->parameters, void *);
	itoa = ft_itoa_u_base(ptr, BASE_HEX_LOW);
	str = ft_printf_padder_add_number_precision(bundle, itoa, 2);
	final = ft_strjoin("0x", ptr == 0 && bundle->flags->precision_enabled &&
						bundle->flags->precision == 0 ? "" : str);
	free(str);
	return (final);
}
