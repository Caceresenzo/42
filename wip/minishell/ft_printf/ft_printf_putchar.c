/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:23:25 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/11 12:23:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void
	ft_printf_putchar(t_ft_printf_settings *settings, char c)
{
	ft_putchar_fd(c, settings->fd);
	settings->written += 1;
}
