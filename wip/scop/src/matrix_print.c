/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:02:30 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/20 19:02:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "matrix.h"

void
m4f_print(const t_m4f *m4)
{
	printf("m4f { %8.4f, %8.4f, %8.4f, %8.4f,\n"
		"      %8.4f, %8.4f, %8.4f, %8.4f,\n"
		"      %8.4f, %8.4f, %8.4f, %8.4f,\n"
		"      %8.4f, %8.4f, %8.4f, %8.4f}\n", //
	m4->m[0][0], m4->m[0][1], m4->m[0][2], m4->m[0][3], //
	m4->m[1][0], m4->m[1][1], m4->m[1][2], m4->m[1][3], //
	m4->m[2][0], m4->m[2][1], m4->m[2][2], m4->m[2][3], //
	m4->m[3][0], m4->m[3][1], m4->m[3][2], m4->m[3][3]);
}