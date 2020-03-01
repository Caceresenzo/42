/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_emptystr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 12:29:14 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/10 12:29:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_emptystr(void)
{
	char	*str;

	if (!(str = malloc(sizeof(char))))
		return (NULL);
	str[0] = '\0';
	return (str);
}
