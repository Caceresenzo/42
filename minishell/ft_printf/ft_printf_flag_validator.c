/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_validator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:40:58 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/08 11:40:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void
	ft_printf_flag_validate(t_ft_printf_flags *flags, int *should_end)
{
	if (flags->valid)
		return ;
	flags->valid = (flags->width_enabled || flags->precision_enabled
					|| flags->hex__upper || flags->hashtag);
	flags->valid = flags->valid && flags->letter != '\0';
	*should_end = flags->letter == '\0';
}
