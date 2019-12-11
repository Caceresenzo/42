/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debugger.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:16:55 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/27 13:16:55 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"

#define F "\t%-22s: "
#define YN(b) ((b) ? "\e[92myes\e[0m" : "\e[96mno\e[0m")

void	ft_printf_debug_dump_flag(t_ft_printf_flags *flags)
{
	printf("{\n");
	printf(F"'%c'\t\t\n", "letter", flags->letter);
	printf(F"%s\t\t\n", "valid", YN(flags->valid));
	printf(F"%s\t\t\n", "minus_sign_used", YN(flags->minus_sign_used));
	printf(F"%d\t\t\n", "side", flags->side);
	printf(F"'%c'\t\t\n", "padding_char", flags->padding_char);
	printf(F"%s\t\t\n", "width_enabled", YN(flags->width_enabled));
	printf(F"%d\t\t\n", "width", flags->width);
	printf(F"%s\t\t\n", "width_negative", YN(flags->width_negative));
	printf(F"%s\t\t\n", "precision_enabled", YN(flags->precision_enabled));
	printf(F"%d\t\t\n", "precision", flags->precision);
	printf(F"%s\t\t\n", "precision_negative", YN(flags->precision_negative));
	printf(F"%s\t\t\n", "hashtag", YN(flags->hashtag));
	printf(F"%s\t\t\n", "hex__upper", YN(flags->hex__upper));
	printf("}\n");
}
