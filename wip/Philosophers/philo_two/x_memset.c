/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_memset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:40:21 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 15:40:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	*x_memset(void *buf, int c, size_t len)
{
	size_t index;

	index = 0;
	while (index < len)
		((unsigned char *)buf)[index++] = c;
	return (buf);
}
