/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:07:16 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 14:07:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_f_char(t_ft_printf_settings *settings,
							t_ft_printf_flags *flags, size_t *index)
{
	char	c;

	FAKE_USE(flags);
	FAKE_USE(index);
	c = (char)va_arg(settings->parameters, int);
	return (ft_chrtostr(c));
}
