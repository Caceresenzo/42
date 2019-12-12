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

void
	ft_printf_format(t_ft_printf_settings *settings, size_t *index)
{
	t_ft_printf_flags	flags;
	void				*formatter;
	size_t				start;
	t_ft_printf_bundle	bundle;

	bundle = (t_ft_printf_bundle) { settings, &flags, index, -1 };
	start = *index;
	ft_printf_flag_initialize(&flags);
	while ((flags.letter = settings->format[*index]))
	{
		formatter = ft_printf_formatter_get(flags.letter);
		if (formatter != NULL || !ft_printf_is_flag_char(flags.letter))
			break ;
		*index += 1;
	}
	if (start != *index)
		ft_printf_flag_parse(&bundle, start, *index);
	ft_printf_format_process(&bundle, formatter);
}

void
	ft_printf_format_process(t_ft_printf_bundle *bundle,
							char *(*formatter)(t_ft_printf_bundle *))
{
	char	*str;

	if (formatter == NULL)
		formatter = &ft_printf_formatter_empty;
	*(bundle->index) += 1;
	str = (*(formatter))(bundle);
	str = ft_printf_flag_handle(bundle, str);
	ft_printf_putstr(str, bundle->settings, bundle->forced_length);
	free(str);
}
