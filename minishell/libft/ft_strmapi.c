/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:24:01 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 13:24:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	index;
	size_t	length;
	char	*str;

	if (!s)
		return (NULL);
	index = 0;
	length = ft_strlen(s);
	if (!(str = ft_calloc(length + 1, sizeof(char))))
		return (NULL);
	while (index < length)
	{
		str[index] = (*f)(index, s[index]);
		index++;
	}
	str[index] = '\0';
	return (str);
}
