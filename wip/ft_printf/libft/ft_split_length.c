/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:43:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 13:43:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_split_length(char **array)
{
	size_t	length;

	if (!array)
		return (0);
	length = 0;
	while (array[length])
		length++;
	return (length);
}
