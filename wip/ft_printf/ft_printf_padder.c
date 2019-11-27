/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:22:40 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/27 16:22:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char
	*ft_printf_padder_add_number_precision(t_ft_printf_bundle *bundle,
											char *abs_itoa, int negative)
{
	int		required;
	char	*zeros;
	char	*str;
	size_t	length;

	length = ft_strlen(abs_itoa);
	required = ft_printf_which_unit(bundle->flags, negative);
	required -= length;
	required = ZERO_IF_NEG(required);
	if (negative == 1)
		required += negative;
	CHECK_PTR_DEF(zeros = ft_charmult('0', required), abs_itoa);
	str = ft_strjoin(zeros, abs_itoa);
	if (negative == 1)
		str[0] = '-';
	free(abs_itoa);
	free(zeros);
	return (str);
}
