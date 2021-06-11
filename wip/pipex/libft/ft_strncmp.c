/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:51:07 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:51:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (!str1 && !str2)
		return (0);
	if (str1 && !str2)
		return (*str1);
	if (!str1 && str2)
		return (*str2);
	while (n-- && *str1 && *str2)
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
