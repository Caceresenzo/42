/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:24:43 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 10:24:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			step;
	size_t			index;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	step = +1;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst > src)
	{
		step = -1;
		dest = (unsigned char *)(dst + len - 1);
		source = (unsigned char *)(src + len - 1);
	}
	index = 0;
	while (index < len)
	{
		*dest = *source;
		dest += step;
		source += step;
		index++;
	}
	return (dst);
}
