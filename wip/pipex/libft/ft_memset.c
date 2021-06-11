/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:13:06 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:13:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void*
	ft_memset(void *dest, char c, size_t n)
{
	char	*cdest;

	if (!dest)
		return (NULL);
	cdest = dest;
	while (n--)
	{
		*cdest = c;
		cdest++;
	}
	return (dest);
}
