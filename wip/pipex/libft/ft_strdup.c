/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 00:22:55 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 00:22:55 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strdup(const char *str)
{
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str) + 1;
	return (ft_memcpy(malloc(len), str, len));
}
