/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_pourcent.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:07:16 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 14:07:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char
	*ft_printf_formatter_pourcent(t_ft_printf_bundle *bundle)
{
	ft_fake_use(&bundle);
	return (ft_chrtostr('%'));
}
