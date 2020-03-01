/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:16:04 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 15:16:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_atoi_base(const char *str, const char *base)
{
	int					radix;
	int					resolved;
	int					negative;
	unsigned long int	result;

	if (!ft_is_base_valid(base))
		return (0);
	radix = ft_strlen(base);
	result = 0;
	negative = 1;
	while (ft_iswspace(*str))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while ((resolved = ft_base_resolve(base, *str)) != -1)
	{
		result *= radix;
		result += resolved;
		str++;
	}
	return (result * negative);
}
