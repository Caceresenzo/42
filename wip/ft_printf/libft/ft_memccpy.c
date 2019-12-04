/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:20:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 16:20:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		index;
	t_uchar		chr;

	chr = c;
	index = 0;
	while (index < n)
	{
		if ((((t_uchar *)dst)[index] = ((t_uchar *)src)[index]) == chr)
			return (dst + index + 1);
		index++;
	}
	return (NULL);
}
