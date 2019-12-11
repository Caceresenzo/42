/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_which_unit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:25:03 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/27 20:25:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	ft_printf_which_unit(t_ft_printf_flags *flags, int offset)
{
	if (flags->width_enabled && flags->precision_enabled)
	{
		if (flags->width_negative && !flags->precision_negative)
			return (flags->precision);
		else if (!flags->width_negative && flags->precision_negative)
			return (flags->padding_char == '0' ? flags->width - offset : 0);
		else if (flags->width_negative && flags->precision_negative)
			return (0);
		else
		{
			if (flags->padding_char == '0' && flags->precision == 0)
				return (flags->precision > flags->width ?
					ft_zero_if_neg(flags->width - offset) : flags->precision);
			else
				return (flags->precision);
		}
	}
	else if (flags->width_enabled && !flags->precision_enabled)
		return (!flags->width_negative && flags->padding_char == '0' ?
				flags->width - offset : 0);
	else if (!flags->width_enabled && flags->precision_enabled)
		return (!flags->precision_negative ? flags->precision : 0);
	return (0);
}
