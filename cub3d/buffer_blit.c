/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_blit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:19:11 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 11:19:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

/*
** From:
** https://github.com/feross/buffer/blob/master/index.js#L1766
*/

size_t
	buffer_blit(t_buffer *buffer, unsigned char *s, size_t offset, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len)
	{
		if (index + offset >= buffer->length)
			break ;
		buffer->data[index + offset] = s[index];
		index++;
	}
	return (index + offset);
}
