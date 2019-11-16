/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrtostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:53:43 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 15:53:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_chrtostr(char c)
{
	char	*str;

	CHECK_MALLOC(str, 2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}
