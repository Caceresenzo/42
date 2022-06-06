/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:37:29 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 20:37:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int
ft_dprintf(int fd, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = ft_vdprintf(fd, format, args);
	va_end(args);
	return (ret);
}

int
ft_vprintf(const char *format, va_list args)
{
	return (ft_vdprintf(1, format, args));
}

int
ft_printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int ret = ft_vdprintf(1, format, args);
	va_end(args);
	return (ret);
}

int
ft_vdprintf(int fd, const char *format, va_list args)
{
	int wrote = 0;

	while (true)
	{
		char letter = *format;
		++format;

		if (!letter)
			break;

		if (letter != '%')
		{
			ssize_t success = write(fd, &letter, 1);
			if (success == -1)
				return (-1);

			wrote += success;
			continue;
		}

		char specifier = *format;
		++format;

		if (!specifier)
			break;

		switch (specifier)
		{
			case 's':
			{
				const char *str = va_arg(args, const char*);

				wrote += ft_putstr_fd(str, fd);

				break;
			}

			case 'c':
			{
				char c = va_arg(args, int);

				wrote += ft_putchar_fd(c, fd);

				break;
			}

			case 'd':
			{
				long n = va_arg(args, int);

				if (n < 0)
				{
					n = -n;
					wrote += ft_putchar_fd('-', fd);
				}

				wrote += ft_putunbr_fd_dec(n, fd);

				break;
			}

			case 'l':
			{
				long n = va_arg(args, long);

				if (n < 0)
				{
					n = -n;
					wrote += ft_putchar_fd('-', fd);
				}

				wrote += ft_putunbr_fd_dec(n, fd);

				break;
			}

			case 'x':
			{
				unsigned long n = va_arg(args, unsigned long);

				wrote += ft_putunbr_fd_hex(n, fd);

				break;
			}

			case 'p':
			{
				void *ptr = va_arg(args, void*);

				wrote += ft_putstr_fd("0x", fd);
				wrote += ft_putunbr_fd_hex((unsigned long)ptr, fd);

				break;
			}

			default:
			{
				wrote += ft_putchar_fd('%', fd);
				wrote += ft_putchar_fd(specifier, fd);

				break;
			}
		}
	}

	return (wrote);
}
