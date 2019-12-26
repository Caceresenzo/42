/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:11:48 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 16:11:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t index;

	if (dst == NULL && src == NULL)
		return (NULL);
	index = 0;
	while (index < n)
	{
		((t_uchar *)dst)[index] = ((t_uchar *)src)[index];
		index++;
	}
	return (dst);
}
