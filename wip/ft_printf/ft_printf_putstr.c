/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:05:06 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 16:05:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_putstr(char *str, t_ft_printf_settings *settings)
{
	CHECK_PTR_EMPTY(str);
	while (*str)
	{
		ft_putchar_fd(*str++, FT_PRINTF_FD);
		settings->written += 1;
	}
}
