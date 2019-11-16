/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formatter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:26:27 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 13:26:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FTPF_SETS t_ft_printf_settings
#define FTPF_FL t_ft_printf_flags

static char	*(*ft_printf_format_get(char key))(FTPF_SETS *, FTPF_FL *, size_t *)
{
	static char		*formatter_key = FT_PRINTF_SUPPORTED_TYPES;
	static char		*(*formatters[9])(FTPF_SETS *, FTPF_FL *, size_t *) = {
			&ft_printf_f_char,
			&ft_printf_f_string,
			&ft_printf_f_pointer,
			&ft_printf_f_decimal,
			&ft_printf_f_decimal,
			&ft_printf_f_uint,
			&ft_printf_f_hex_int,
			&ft_printf_f_hex_int,
			&ft_printf_f_pourcent
	};
	size_t			index;

	index = 0;
	while (formatter_key[index])
	{
		if (formatter_key[index] == key)
			return (formatters[index]);
		index++;
	}
	return (NULL);
}

static int	internal_ft_printf_format_is_invalid_char(char c)
{
	if (ft_isdigit(c) || c == '#' || c == '-' || c == '.' || c == '*')
		return (0);
	return (1);
}

void		ft_printf_format(t_ft_printf_settings *settings, size_t *index)
{
	t_ft_printf_flags	flags;
	char				*(*formatter)(FTPF_SETS *, FTPF_FL *, size_t *);
	size_t				start;
	char				*str;

	start = *index;
	ft_printf_flag_initialize(&flags);
	while ((flags.letter = settings->format[*index]))
	{
		formatter = ft_printf_format_get(flags.letter);
		if (formatter != NULL
				|| internal_ft_printf_format_is_invalid_char(flags.letter))
			break ;
		*index += 1;
	}
	if (start != *index)
		ft_printf_flag_parse(settings, &flags, start, *index);
	if (formatter != NULL)
	{
		*index += 1;
		str = (*(formatter))(settings, &flags, index);
		str = ft_printf_flag_handle(&flags, str);
		ft_printf_putstr(str, settings);
		free(str);
	}
}
