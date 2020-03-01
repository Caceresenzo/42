/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:07:16 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 14:07:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char
	*ft_printf_formatter_string(t_ft_printf_bundle *bundle)
{
	char	*str;

	str = va_arg(bundle->settings->parameters, char *);
	if (str == NULL)
		str = "(null)";
	if (bundle->flags->precision_enabled && !bundle->flags->precision_negative)
		return (ft_substr(str, 0, bundle->flags->precision));
	return (ft_strdup(str));
}
