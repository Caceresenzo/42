/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:47:39 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 16:47:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		i_ft_printf_flag_parse_value(t_ft_printf_settings *settings,
												char *str, size_t *index)
{
	int		value;

	if (str[*index] == '*')
	{
		value = va_arg(settings->parameters, int);
		*index += 1;
	}
	else
	{
		value = ft_atoi(str + *index);
		*index += ft_itoa_base_compute_number_size(value, 10) - 1;
	}
	return (value);
}

static void		i_ft_printf_flag_parse_width(t_ft_printf_settings *settings,
												t_ft_printf_flags *flags,
												char *str, size_t *index)
{
	int		value;

	if (flags->width_enabled)
		return ;
	flags->width_enabled = 1;
	value = i_ft_printf_flag_parse_value(settings, str, index);
	if (value < 0)
	{
		flags->side = !flags->side;
		value *= -1;
		flags->width_negative = 1;
	}
	flags->width = value;
}

static void		i_ft_printf_flag_parse_precision(size_t *index,
												t_ft_printf_settings *settings,
												t_ft_printf_flags *flags,
												char *str)
{
	int		value;

	*index += 1;
	if (flags->precision_enabled)
		return ;
	flags->precision_enabled = 1;
	value = i_ft_printf_flag_parse_value(settings, str, index);
	if (value < 0)
	{
		value *= -1;
		flags->precision_negative = 1;
	}
	flags->precision = value;
}

static void		i_ft_printf_flag_parse_commit(t_ft_printf_settings *settings,
										t_ft_printf_flags *flags, char *str,
										size_t *index)
{
	char	current;

	current = str[*index];
	if (current == '-')
	{
		flags->minus_sign_used = 1;
		flags->padding_char = ' ';
		flags->side = 1;
	}
	else if (current == '#')
		flags->hashtag = 1;
	else if (current == '0')
	{
		if (!flags->minus_sign_used)
			flags->padding_char = '0';
	}
	else
	{
		i_ft_printf_flag_parse_width(settings, flags, str, index);
		if ((current = str[*index]) == '.')
			i_ft_printf_flag_parse_precision(index, settings, flags, str);
	}
}

void			ft_printf_flag_parse(t_ft_printf_settings *settings,
										t_ft_printf_flags *flags, size_t start,
										size_t end)
{
	size_t	length;
	char	*str;
	size_t	index;

	length = end - start;
	CHECK_PTR_EMPTY(str = malloc((length + 1) * sizeof(char)));
	ft_memcpy(str, settings->format + start, length);
	str[length] = '\0';
	index = 0;
	while (index < length)
	{
		i_ft_printf_flag_parse_commit(settings, flags, str, &index);
		index++;
	}
	i_ft_printf_flag_parse_commit(settings, flags, str, &index);
	free(str);
	ft_printf_flag_validate(flags);
}
