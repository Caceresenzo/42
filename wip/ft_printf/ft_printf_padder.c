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
											char *abs_itoa, int negative,
											int offset)
{
	int		required;
	char	*zeros;
	char	*str;
	size_t	length;

	length = ft_strlen(abs_itoa);
	required = ft_printf_which_unit(bundle->flags, negative + offset);
	required -= length;
	required = ft_zero_if_neg(required);
	if (negative)
		required++;
	if (!(zeros = ft_chrmult('0', required)))
		return (abs_itoa);
	str = ft_strjoin_free(zeros, abs_itoa, FT_STRJOIN_FREE_BOTH);
	if (negative)
		str[0] = '-';
	return (str);
}
