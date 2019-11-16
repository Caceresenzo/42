/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charmult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:45:01 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 17:45:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_charmult(char c, size_t times)
{
	char	*str;

	CHECK_MALLOC(str, (times + 1) * sizeof(char));
	ft_memset(str, c, times);
	str[times] = '\0';
	return (str);
}
