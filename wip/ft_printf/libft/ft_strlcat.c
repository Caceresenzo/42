/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:42:14 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 17:42:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*dest;
	char	*source;
	size_t	dst_length;
	size_t	remaing;

	dest = dst;
	source = (char *)src;
	remaing = dstsize;
	while (remaing-- != 0 && *dest != '\0')
		dest++;
	dst_length = dest - dst;
	remaing = dstsize - dst_length;
	if (remaing == 0)
		return (dst_length + ft_strlen(source));
	while (*source != '\0')
	{
		if (remaing > 1)
		{
			*dest++ = *source;
			remaing--;
		}
		source++;
	}
	*dest = '\0';
	return (dst_length + (source - src));
}
