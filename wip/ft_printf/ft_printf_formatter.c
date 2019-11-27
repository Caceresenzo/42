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

static int
	internal_ft_printf_format_is_invalid_char(char c)
{
	if (ft_isdigit(c) || c == '#' || c == '-' || c == '.' || c == '*')
		return (0);
	return (1);
}

void
	ft_printf_format(t_ft_printf_settings *settings, size_t *index)
{
	t_ft_printf_flags	flags;
	void				*formatter;
	size_t				start;

	start = *index;
	ft_printf_flag_initialize(&flags);
	while ((flags.letter = settings->format[*index]))
	{
		formatter = ft_printf_formatter_get(flags.letter);
		if (formatter != NULL
				|| internal_ft_printf_format_is_invalid_char(flags.letter))
			break ;
		*index += 1;
	}
	if (start != *index)
		ft_printf_flag_parse(settings, &flags, start, *index);
	ft_printf_format_process((t_ft_printf_bundle) {
		settings, &flags, index, -1
	}, formatter);
}

void
	ft_printf_format_process(t_ft_printf_bundle bundle,
							char *(*formatter)(t_ft_printf_bundle *))
{
	char	*str;

	if (formatter == NULL)
		formatter = &ft_printf_formatter_empty;
	*(bundle.index) += 1;
	str = (*(formatter))(&bundle);
	str = ft_printf_flag_handle(&bundle, str);
	ft_printf_putstr(str, bundle.settings, bundle.forced_length);
	free(str);
}
