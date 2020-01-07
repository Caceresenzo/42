/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:39:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 16:39:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	ft_strjoin_split_total_length(char **split, size_t split_size)
{
	size_t	total_length;
	size_t	index;

	total_length = 0;
	index = 0;
	while (index < split_size)
	{
		total_length += ft_strlen(split[index]);
		index++;
	}
	return (total_length);
}

char
	*ft_strjoin_split(char **split)
{
	char	*str;
	size_t	split_size;
	size_t	total_length;
	size_t	indexes[2];
	size_t	length;

	if (!split)
		return (NULL);
	split_size = ft_split_length(split);
	total_length = ft_strjoin_split_total_length(split, split_size);
	if (!(str = malloc((total_length + 1) * sizeof(char))))
		return (NULL);
	str[total_length] = '\0';
	ft_bzero(&indexes, sizeof(indexes));
	while (indexes[0] < split_size)
	{
		length = ft_strlen(split[indexes[0]]);
		ft_memcpy(str + indexes[1], split[indexes[0]], length);
		indexes[0] += 1;
		indexes[1] += length;
	}
	return (str);
}
