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

char	*ft_printf_f_string(t_ft_printf_settings *settings,
							t_ft_printf_flags *flags, size_t *index)
{
	char	*str;

	FAKE_USE(index);
	str = va_arg(settings->parameters, char *);
	if (str == NULL)
		str = "(null)";
	if (flags->precision_enabled)
		return (ft_substr(str, 0, flags->precision));
	return (ft_strdup(str));
}
