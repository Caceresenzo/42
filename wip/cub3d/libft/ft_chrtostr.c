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

#include "libft.h"

char
	*ft_chrtostr(char c)
{
	char	*str;

	if (!(str = malloc(2 * sizeof(char))))
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}
