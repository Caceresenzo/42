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

void
	ft_printf_putstr(char *str, t_ft_printf_settings *settings, int length)
{
	int		index;

	if (!str || length == 0)
		return ;
	if (length == -1)
		while (*str)
			ft_printf_putchar(settings, *str++);
	else
	{
		index = 0;
		while (index < length)
			ft_printf_putchar(settings, str[index++]);
	}
}
