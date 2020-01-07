/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:43:09 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 13:43:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_split_free(char ***split_ptr)
{
	size_t	length;
	size_t	index;

	if (!split_ptr || !*split_ptr)
		return (NULL);
	length = ft_split_length(*split_ptr);
	index = 0;
	while (index < length)
	{
		free((*split_ptr)[index]);
		index++;
	}
	free(*split_ptr);
	*split_ptr = NULL;
	return (NULL);
}
