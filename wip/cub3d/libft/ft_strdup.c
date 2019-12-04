/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:01:57 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/04 20:01:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strdup(const char *s1)
{
	size_t	length;
	char	*duplicate;

	length = ft_strlen(s1);
	if (!(duplicate = ft_calloc(length + 1, sizeof(char))))
		return (NULL);
	ft_memcpy(duplicate, s1, length);
	duplicate[length] = '\0';
	return (duplicate);
}
