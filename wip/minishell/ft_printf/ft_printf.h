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

# include "../libft/libft.h"

# define FT_PRINTF_CHAR_FORMAT '%'
# define FT_PRINTF_SUPPORTED_TYPES "cspdiuxX%o"
# define FT_PRINTF_FD OUT

typedef	struct	s_ft_printf_settings
{
	int			written;
	const char	*format;
	va_list		parameters;
	int			fd;
	int			end;
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

typedef struct	s_ft_printf_bundle
{
	t_ft_printf_settings	*settings;
	t_ft_printf_flags		*flags;
	size_t					*index;
	int						forced_length;
}				t_ft_printf_bundle;

int				ft_dprintf(int fd, const char *format, ...);
int				ft_vprintf(const char *format, va_list args);
int				ft_vdprintf(int fd, const char *format, va_list args);
int				ft_printf(const char *format, ...);

void			ft_printf_handle(t_ft_printf_settings *settings);

void			ft_printf_format(t_ft_printf_settings *settings, size_t *index);
void			ft_printf_format_process(t_ft_printf_bundle *bundle,
							char *(*formatter)(t_ft_printf_bundle *));

void			ft_printf_putstr(char *str, t_ft_printf_settings *settings,
								int length);
void			ft_printf_putchar(t_ft_printf_settings *settings, char c);

void			ft_printf_flag_initialize(t_ft_printf_flags *flags);
void			ft_printf_flag_parse(t_ft_printf_bundle *bundle, size_t start,
										size_t end);
char			*ft_printf_flag_handle(t_ft_printf_bundle *bundle,
										char *formatted);

void			ft_printf_flag_validate(t_ft_printf_flags *flags,
										int *should_end);

void			*ft_printf_formatter_get(char key);

char			*ft_printf_formatter_char(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_string(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_pointer(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_decimal(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_uint(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_hex_int(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_pourcent(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_octal_int(t_ft_printf_bundle *bundle);
char			*ft_printf_formatter_empty(t_ft_printf_bundle *bundle);

int				ft_printf_f_decimal_should_be_empty(int equal_zero,
											t_ft_printf_flags *flags);

size_t			ft_itoa_base_compute_number_size(long number, size_t radix);

void			ft_printf_debug_dump_flag(t_ft_printf_flags *flags);

char			*ft_printf_padder_add_number_precision(t_ft_printf_bundle *b,
											char *abs_itoa, int negative,
											int offset);
int				ft_printf_which_unit(t_ft_printf_flags *flags, int offset);

int				ft_printf_is_flag_char(char c);

#endif
