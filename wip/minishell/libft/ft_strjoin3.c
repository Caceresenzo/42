/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:55:28 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 13:55:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	if (!(str = malloc((s1_len + s2_len + s3_len) + 1)))
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	ft_memcpy(str + s1_len + s2_len, s3, s3_len);
	str[s1_len + s2_len + s3_len] = '\0';
	return (str);
}
