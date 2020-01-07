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
	*ft_printf_formatter_empty(t_ft_printf_bundle *bundle)
{
	if (bundle->flags->precision_enabled)
		bundle->flags->precision_enabled = 0;
	if (bundle->flags->letter == '\0')
		return (ft_emptystr());
	bundle->forced_length = 1;
	return (ft_chrtostr(bundle->flags->letter));
}
