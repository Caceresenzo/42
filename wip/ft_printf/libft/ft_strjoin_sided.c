/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sided.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:18:39 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 16:18:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin_sided(char const *s1, char const *s2, int side)
{
	if (side)
		return (ft_strjoin(s2, s1));
	return (ft_strjoin(s1, s2));
}
