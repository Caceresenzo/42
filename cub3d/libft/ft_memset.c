/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:40:21 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 15:40:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memset(void *b, int c, size_t len)
{
	size_t index;

	index = 0;
	while (index < len)
		((t_uchar *)b)[index++] = c;
	return (b);
}
