/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:21:47 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 12:21:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_itoa_nsize(long number)
{
	size_t	size;

	size = (number < 0 ? 1 : 0);
	while (1)
	{
		number /= 10;
		size++;
		if (number == 0)
			break ;
	}
	return (size);
}

char
	*ft_itoa(int n)
{
	long	number;
	char	*array;
	size_t	size;

	number = n;
	size = ft_itoa_nsize(n);
	if (!(array = malloc((size + 1) * sizeof(char))))
		return (NULL);
	if (number < 0)
	{
		array[0] = '-';
		number *= -1;
	}
	array[size] = '\0';
	while (1)
	{
		array[size - 1] = (number % 10) + '0';
		number /= 10;
		size--;
		if (number == 0)
			break ;
	}
	return (array);
}
