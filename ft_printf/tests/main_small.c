/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:44:39 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/26 15:44:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

#define X(format, ...) \
	printf("\e[1m\e[7m\e[92m\e[107m--------------------------------\e[0m\n"); \
	printf("\e[95m...\e[0m"); \
	r1 = printf(format, ##__VA_ARGS__); \
	fflush(stdout); \
	printf("\e[95m...\e[0m\n\e[95m...\e[0m"); \
	fflush(stdout); \
	r2 = ft_printf(format, ##__VA_ARGS__); \
	printf("\e[95m...\e[0m\n"); \
	fflush(stdout); \
	if (r1 != r2) \
	{ \
		printf("\e[91mReturn ERROR: \e[32m%d \e[97m!= \e[32m%d\e[0m\n", r1, r2); \
		printf("\e[1m\e[7m\e[91m\e[107m--------------------------------\e[0m\n\n\n"); \
	}

int
	main(int argc, char **argv)
{
	int r1;
	int r2;

	X("%.*d", 3, 0);
	X("%.5*d", 3, 0);
	X("%.1*d", 3, 0);
	X("%.0*d", 3, 0);
	X("%.00*d", 3, 0);
	X("%*.0d", 3, 0);
}
