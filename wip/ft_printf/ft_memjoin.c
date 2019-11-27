/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:58:36 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/27 15:58:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_memjoin(void *s1, size_t length1, void *s2, size_t length2)
{
	char	*str;

	CHECK_PTR(s1);
	CHECK_PTR(s2);
	CHECK_MALLOC(str, length1 + length2);
	ft_memcpy(str, s1, length1);
	ft_memcpy(str + length1, s2, length2);
	return (str);
}
