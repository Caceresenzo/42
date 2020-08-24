/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:22:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:22:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t
	long_nbr_size(unsigned long nbr)
{
	size_t	size;

	size = 0;
	while (1)
	{
		size++;
		if (!(nbr /= 10))
			break ;
	}
	return (size);
}

size_t
	ft_sputnbr(char *to, unsigned long nbr)
{
	size_t	size;
	size_t	index;

	size = long_nbr_size(nbr);
	index = size;
	while (1)
	{
		to[--index] = '0' + (nbr % 10);
		if (!(nbr /= 10))
			break ;
	}
	return (size);
}
