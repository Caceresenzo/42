/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:29:48 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 16:29:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_printf_flag_handle_width(t_ft_printf_flags *flags, char *formatted)
{
	size_t	length;
	int		required;
	char	*padding;
	char	*str;

	if (flags->precision_enabled)
		flags->padding_char = ' ';
	length = ft_strlen(formatted);
	required = flags->width - length;
	if (required <= 0)
		return (formatted);
	padding = ft_charmult(flags->padding_char, required);
	CHECK_PTR_DEF(padding, formatted);
	if (flags->side)
		str = ft_strjoin(formatted, padding);
	else
		str = ft_strjoin(padding, formatted);
	free(padding);
	return (str);
}

char	*ft_printf_flag_handle(t_ft_printf_flags *flags, char *formatted)
{
	char *str;

	if (!flags->valid)
		return (formatted);
	str = formatted;
	if (flags->width_enabled)
		str = ft_printf_flag_handle_width(flags, str);
	if (str != formatted)
		free(formatted);
	return (str);
}
