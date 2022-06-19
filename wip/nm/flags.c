/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:02:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 18:02:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>

#include "nm.h"

bool
flags_parse(t_flags *flags, int argc, char **argv, int *file_index)
{
	if (!flags)
		return (false);

	for (int index = 1; index < argc; index++)
	{
		const char *arg = argv[index];

		if (arg && arg[0] == '-')
		{
			if (arg[1] == '-')
			{
				if (!flags_parse_word(flags, arg + 2))
					return (false);
			}
			else
			{
				++arg;
				while (*arg)
				{
					if (!flags_parse_letter(flags, *arg))
						return (false);
					++arg;
				}
			}
		}
		else
		{
			*file_index = index;
			break;
		}
	}
	return (true);
}

bool
flags_parse_letter(t_flags *flags, char letter)
{
	switch (letter)
	{
		case 'h':
		{
			flags->help = true;

			return (true);
		}

		case 'V':
		{
			flags->version = true;

			return (true);
		}

		case 'a':
		{
			flags->include_all = true;
			flags->only_extern = false;
			flags->only_undefined = false;

			return (true);
		}

		case 'g':
		{
			flags->include_all = false;
			flags->only_extern = true;
			flags->only_undefined = false;

			return (true);
		}

		case 'u':
		{
			flags->include_all = false;
			flags->only_extern = false;
			flags->only_undefined = true;

			return (true);
		}

		case 'r':
		{
			flags->sort_reverse = true;

			return (true);
		}

		case 'n':
		{
			flags->sort = SORT_NUMERIC;

			return (true);
		}

		case 'p':
		{
			flags->sort = SORT_NONE;

			return (true);
		}

		default:
		{
			flags->unknown_letter = letter;
			return (false);
		}
	}
}

bool
flags_parse_word(t_flags *flags, const char *word)
{
	if (ft_strcmp("help", word) == 0)
		return (flags_parse_letter(flags, 'h'));

	if (ft_strcmp("version", word) == 0)
		return (flags_parse_letter(flags, 'V'));

	if (ft_strcmp("debug-syms", word) == 0)
		return (flags_parse_letter(flags, 'a'));

	if (ft_strcmp("extern-only", word) == 0)
		return (flags_parse_letter(flags, 'g'));

	if (ft_strcmp("undefined-only", word) == 0)
		return (flags_parse_letter(flags, 'u'));

	if (ft_strcmp("numeric-sort", word) == 0)
		return (flags_parse_letter(flags, 'n'));

	if (ft_strcmp("reverse-sort", word) == 0)
		return (flags_parse_letter(flags, 'r'));

	if (ft_strcmp("no-sort", word) == 0)
		return (flags_parse_letter(flags, 'p'));

	flags->unknown_word = word;
	return (false);
}
