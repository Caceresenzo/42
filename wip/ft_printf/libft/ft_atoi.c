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
	ft_atoi(const char *str)
{
	size_t				index;
	int					negative;
	unsigned long int	result;

	index = 0;
	negative = 1;
	result = 0;
	while (ft_iswspace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
		if (str[index++] == '-')
			negative *= -1;
	while (ft_isdigit(str[index]))
	{
		result *= 10;
		result += str[index] - '0';
		index++;
	}
	return (result * negative);
}
