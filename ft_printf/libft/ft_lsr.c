/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:56:25 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 11:56:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Logical Shift Right, a simple right bit shifting but that complete with zeros
** From:
** https://stackoverflow.com/a/5253269/7292958
*/

int
	ft_lsr(int x, int n)
{
	return (int)((unsigned int)x >> n);
}
