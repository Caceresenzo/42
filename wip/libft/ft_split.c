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
#include <stdio.h>

static size_t	internal_ft_split_compute_items(char const *s, char c)
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

static void		internal_ft_split_do(char const *s, char c, char **array,
										size_t item_count)
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
				CHECK_PTR_EMPTY(str = ft_calloc(length + 1, sizeof(char)));
				ft_memcpy(str, s + index - length, length);
				array[array_index] = str;
				array_index++;
			}
			length = 0;
		}
		else
			length++;
		index++;
	}
}

char			**ft_split(char const *s, char c)
{
	size_t	item_count;
	char	**array;

	CHECK_PTR(s);
	item_count = internal_ft_split_compute_items(s, c);
	CHECK_MALLOC(array, (item_count + 1) * sizeof(char *));
	internal_ft_split_do(s, c, array, item_count);
	array[item_count] = NULL;
	return (array);
}
