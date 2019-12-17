/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	atoi_test(char *str, char *base)
{
	printf("%20d %d\n", ft_atoi_base_2(str, base), ft_atoi_base(str, base));
}

void
	test_ft_atoi_base(void)
{
	printf("%20s %s\n", "WORKING", "ASSEMBLY");
	atoi_test("   -123", "01");
	atoi_test("   -123", "01234567890");
	atoi_test("-123000", "0123456789");
	atoi_test(" +1230000000", "0123456789ABCDEF");
	atoi_test("   -123", "01");
	atoi_test("-123000", "0123456789");
	atoi_test(" \n +2147483647", "0123456789");
	atoi_test("  -2147483648", "0123456789");
	atoi_test("--ff", "0123456789abcdef");
	atoi_test("10", "011");
	atoi_test("10111", "0\v541");
	atoi_test("10111", "+0\v541");
}
