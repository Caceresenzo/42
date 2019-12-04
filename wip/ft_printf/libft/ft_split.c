/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:05:13 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/06 11:05:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t
	i_ft_split_compute_items(char const *s, char c)
{
	size_t	index;
	size_t	count;
	size_t	length;

	index = 0;
	count = 0;
	length = 0;
	while (s[index])
	{
		if (s[index] == c)
		{
			if (length != 0)
				count++;
			length = 0;
		}
		else
			length++;
		index++;
	}
	return (count + (length != 0 ? 1 : 0));
}

static void
	i_ft_split_do(char const *s, char c, char **array, size_t item_count)
{
	char	*str;
	size_t	array_index;
	size_t	index;
	size_t	length;

	array_index = 0;
	index = 0;
	length = 0;
	while (array_index < item_count)
	{
		if (s[index] == c || s[index] == '\0')
		{
			if (length != 0)
			{
				if (!(str = ft_calloc(length + 1, sizeof(char))))
					return ;
				ft_memcpy(str, s + index - length, length);
				array[array_index++] = str;
			}
			length = 0;
		}
		else
			length++;
		index++;
	}
}

char
	**ft_split(char const *s, char c)
{
	size_t	item_count;
	char	**array;

	if (!s)
		return (NULL);
	item_count = i_ft_split_compute_items(s, c);
	if (!(array = malloc((item_count + 1) * sizeof(char *))))
		return (NULL);
	i_ft_split_do(s, c, array, item_count);
	array[item_count] = NULL;
	return (array);
}
