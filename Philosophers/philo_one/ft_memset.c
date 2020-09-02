/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:15:39 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:15:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	*ft_memset(void *src, int c, size_t n)
{
	unsigned char *ptr;

	if ((ptr = src))
		while (n--)
			*ptr++ = (unsigned char)c;
	return (src);
}
