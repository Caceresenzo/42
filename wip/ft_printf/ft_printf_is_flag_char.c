/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_is_flag_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:24:44 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 15:24:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	ft_printf_is_flag_char(char c)
{
	if (ft_isdigit(c) || ft_strcontain("#-.*+ lh", c))
		return (1);
	return (0);
}
