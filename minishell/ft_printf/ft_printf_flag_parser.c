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

static int
	i_ft_printf_flag_parse_value(t_ft_printf_bundle *bundle, char *str)
{
	int		value;

	if (str[*(bundle->index)] == '*')
	{
		value = va_arg(bundle->settings->parameters, int);
		*(bundle->index) += 1;
	}
	else
	{
		value = ft_atoi(str + *(bundle->index));
		*(bundle->index) += ft_itoa_base_nsize(value, 10) - 1;
	}
	return (value);
}

static void
	i_ft_printf_flag_parse_width(t_ft_printf_bundle *bundle, char *str)
{
	int		value;

	bundle->flags->width_enabled = 1;
	value = i_ft_printf_flag_parse_value(bundle, str);
	if (value < 0)
	{
		bundle->flags->side = 1;
		value *= -1;
		bundle->flags->width_negative = 1;
		bundle->flags->padding_char = ' ';
	}
	bundle->flags->width = value;
}

static void
	i_ft_printf_flag_parse_precision(t_ft_printf_bundle *bundle, char *str)
{
	int		value;
	size_t	zero_skip;

	*(bundle->index) += 1;
	zero_skip = 0;
	while ((str[*(bundle->index) + zero_skip]) == '0')
		zero_skip++;
	bundle->flags->precision_enabled = 1;
	value = i_ft_printf_flag_parse_value(bundle, str);
	if (value < 0)
	{
		value *= -1;
		bundle->flags->precision_negative = 1;
	}
	bundle->flags->precision = value;
	*(bundle->index) += zero_skip;
	if (value == 0)
		*(bundle->index) -= 1;
}

static void
	i_ft_printf_flag_parse_commit(t_ft_printf_bundle *bundle, char *str)
{
	char	current;

	current = str[*(bundle->index)];
	if (current == '-')
	{
		bundle->flags->minus_sign_used = 1;
		bundle->flags->padding_char = ' ';
		bundle->flags->side = 1;
	}
	else if (current == '#')
		bundle->flags->hashtag = 1;
	else if (current == '0')
	{
		if (!bundle->flags->minus_sign_used)
			bundle->flags->padding_char = '0';
	}
	else
	{
		if ((current = str[*(bundle->index)]) != '.')
			i_ft_printf_flag_parse_width(bundle, str);
		if ((current = str[*(bundle->index)]) == '.')
			i_ft_printf_flag_parse_precision(bundle, str);
	}
}

void
	ft_printf_flag_parse(t_ft_printf_bundle *bundle, size_t start, size_t end)
{
	size_t	length;
	char	*str;
	size_t	index;
	size_t	*old_index;

	length = end - start;
	if (!(str = malloc((length + 1) * sizeof(char))))
		return ;
	ft_memcpy(str, bundle->settings->format + start, length);
	str[length] = '\0';
	index = 0;
	old_index = bundle->index;
	bundle->index = &index;
	while (index < length)
	{
		i_ft_printf_flag_parse_commit(bundle, str);
		index++;
	}
	bundle->index = old_index;
	free(str);
	ft_printf_flag_validate(bundle->flags, &(bundle->settings->end));
}
