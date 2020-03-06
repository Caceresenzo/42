/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:08:48 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 13:08:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	ft_vprintf(const char *format, va_list args)
{
	t_ft_printf_settings settings;

	settings.format = format;
	settings.written = 0;
	settings.fd = FT_PRINTF_FD;
	va_copy(settings.parameters, args);
	ft_printf_handle(&settings);
	va_end(settings.parameters);
	return (settings.written);
}
