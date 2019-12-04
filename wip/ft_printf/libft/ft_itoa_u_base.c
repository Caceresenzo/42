/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:21:47 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 12:21:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_itoa_u_base_nsize(unsigned long number, size_t radix)
{
	size_t	size;

	size = 0;
	while (1)
	{
		number /= radix;
		size++;
		if (number == 0)
			break ;
	}
	return (size);
}

char
	*ft_itoa_u_base(unsigned long n, char *base)
{
	long long	number;
	size_t		radix;
	char		*array;
	size_t		size;

	number = n;
	radix = ft_strlen(base);
	size = ft_itoa_u_base_nsize(n, radix);
	if (!(array = malloc((size + 1) * sizeof(char))))
		return (NULL);
	array[size] = '\0';
	while (1)
	{
		array[size - 1] = base[(number % radix)];
		number /= radix;
		size--;
		if (number == 0)
			break ;
	}
	return (array);
}
