/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:06:57 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/07 13:06:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>

# include "libft/libft.h"

# define FT_PRINTF_CHAR_FORMAT '%'
# define FT_PRINTF_SUPPORTED_TYPES "cspdiuxX%"
# define FT_PRINTF_FD OUT

# define BASE_DECIMAL "0123456789"
# define BASE_HEX_LOW "0123456789abcdef"
# define BASE_HEX_UP "0123456789ABCDEF"

# define FAKE_USE(var) ((void) var);

# define ABS(number) (number < 0 ? -number : number)
# define ZERO_IF_NEG(number) (number <= 0 ? 0 : number)

typedef	struct	s_ft_printf_settings
{
	int			written;
	const char	*format;
	va_list		parameters;
}				t_ft_printf_settings;

typedef	struct	s_ft_printf_flags
{
	char		letter;
	int			valid;
	int			minus_sign_used;
	int			side;
	char		padding_char;
	int			width_enabled;
	int			width;
	int			width_negative;
	int			precision_enabled;
	int			precision;
	int			precision_negative;
	int			hashtag;
	int			hex__upper;
}				t_ft_printf_flags;

int				ft_printf(const char *format, ...);
void			ft_printf_handle(t_ft_printf_settings *settings);
void			ft_printf_format(t_ft_printf_settings *settings, size_t *index);
void			ft_printf_putstr(char *str, t_ft_printf_settings *settings);

void			ft_printf_flag_initialize(t_ft_printf_flags *flags);
void			ft_printf_flag_parse(t_ft_printf_settings *settings,
										t_ft_printf_flags *flags, size_t start,
										size_t end);
char			*ft_printf_flag_handle(t_ft_printf_flags *flags,
										char *formatted);

void			ft_printf_flag_validate(t_ft_printf_flags *flags);

char			*ft_printf_f_char(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_string(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_pointer(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_decimal(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_uint(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_hex_int(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_pourcent(t_ft_printf_settings *settings,
									t_ft_printf_flags *flags, size_t *index);
char			*ft_printf_f_null(t_ft_printf_settings *settings, int read_arg);

int				ft_printf_f_decimal_should_be_empty(int equal_zero,
											t_ft_printf_flags *flags);

char			*ft_emptystr(void);
char			*ft_chrtostr(char c);
char			*ft_charmult(char c, size_t times);
char			*ft_itoa_base(long n, char *base);
size_t			ft_itoa_base_compute_number_size(long number, size_t radix);

void			ft_printf_debug_dump_flag(t_ft_printf_flags *flags);

#endif
