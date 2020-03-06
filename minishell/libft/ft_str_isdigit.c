/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 16:20:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 16:20:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_str_isdigit(char *str, int allow_signs, int max_sign)
{
	while (ft_iswspace(*str))
		str++;
	if (allow_signs && *str)
	{
		while (max_sign != 0 && *str)
		{
			if (*str == '-' || *str == '+')
				max_sign--;
			else
				break ;
			str++;
		}
	}
	while (*str)
	{
		if (!ft_isdigit(*str) && !ft_iswspace(*str))
			return (0);
		str++;
	}
	return (1);
}
