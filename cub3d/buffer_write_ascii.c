/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:13:50 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 11:13:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

/*
** From:
** https://github.com/feross/buffer/blob/master/index.js#L845
*/

static char
	buffer_ascii_map(unsigned int index, char old)
{
	ft_fake_use(&index);
	return (((unsigned char)old) & 0xFF);
}

size_t
	buffer_write_ascii(t_buffer *buffer, char *s, size_t offset, size_t length)
{
	unsigned char	*bytes;
	size_t			new_pos;

	bytes = (unsigned char *)ft_strmapi(s, &buffer_ascii_map);
	if (!bytes)
		return ((size_t)-1);
	new_pos = buffer_blit(buffer, bytes, offset, length);
	free(bytes);
	return (new_pos);
}
