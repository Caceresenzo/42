/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 00:25:20 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 00:25:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	if (!dest || !src)
		return (dest);
	cdest = dest;
	csrc = src;
	while (n--)
	{
		*cdest = *csrc;
		cdest++;
		csrc++;
	}
	return (dest);
}
