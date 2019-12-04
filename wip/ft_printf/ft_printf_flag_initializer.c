/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_initializer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:48:11 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 16:48:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void
	ft_printf_flag_initialize(t_ft_printf_flags *flags)
{
	flags->letter = '\0';
	flags->valid = 0;
	flags->minus_sign_used = 0;
	flags->side = 0;
	flags->padding_char = ' ';
	flags->hashtag = 0;
	flags->width_enabled = 0;
	flags->width = 0;
	flags->width_negative = 0;
	flags->precision_enabled = 0;
	flags->precision = 0;
	flags->precision_negative = 0;
	flags->hex__upper = 0;
}
