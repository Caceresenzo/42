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

char
	*ft_printf_flag_handle_width(t_ft_printf_bundle *bundle, char *formatted)
{
	size_t	length;
	int		required;
	char	*padding;
	char	*str;
	char	letter;

	letter = ft_tolower(bundle->flags->letter);
	if ((bundle->flags->precision_enabled || bundle->flags->precision_negative)
			&& !ft_strcontain("s%", letter) && ((letter != 'x' && letter != 'o')
			|| bundle->flags->precision < bundle->flags->width))
	{
		bundle->flags->padding_char = ' ';
	}
	length = ft_strlen(formatted);
	required = bundle->flags->width - length;
	if (required < 0)
		return (formatted);
	padding = ft_chrmult(bundle->flags->padding_char, required);
	if (!padding)
		return (formatted);
	str = ft_strjoin_sided(padding, formatted, bundle->flags->side);
	bundle->forced_length = required + length;
	free(padding);
	return (str);
}

char
	*ft_printf_flag_handle_width_m(t_ft_printf_bundle *bundle, char *formatted)
{
	size_t	length;
	int		required;
	char	*padding;
	char	*str;

	if (bundle->flags->precision_enabled
			&& bundle->flags->precision != 0 && bundle->flags->letter != 'c')
		bundle->flags->padding_char = ' ';
	length = bundle->forced_length;
	required = bundle->flags->width - length;
	if (required < 0)
		return (formatted);
	padding = ft_chrmult(bundle->flags->padding_char, required);
	if (!padding)
		return (formatted);
	if (bundle->flags->side)
		str = ft_memjoin(formatted, length, padding, required);
	else
		str = ft_memjoin(padding, required, formatted, length);
	bundle->forced_length = required + length;
	free(padding);
	return (str);
}

char
	*ft_printf_flag_handle(t_ft_printf_bundle *bundle, char *formatted)
{
	char *str;

	if (!bundle->flags->valid)
		return (formatted);
	str = formatted;
	if (bundle->flags->width_enabled)
	{
		if (bundle->forced_length == -1)
			str = ft_printf_flag_handle_width(bundle, str);
		else
			str = ft_printf_flag_handle_width_m(bundle, str);
	}
	if (str != formatted)
		free(formatted);
	return (str);
}
