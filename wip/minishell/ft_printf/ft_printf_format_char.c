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

char
	*ft_printf_formatter_char(t_ft_printf_bundle *bundle)
{
	char	c;

	c = (char)va_arg(bundle->settings->parameters, int);
	bundle->forced_length = 1;
	return (ft_chrtostr(c));
}
