/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 15:44:39 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/26 15:44:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>

#include "libft/libft.h"
#include "ft_printf.h"

#define LIBC_PRINTF_FILE "libc_output.txt"
#define FT_PRINTF_FILE "user_output.txt"

#define REDIRECT(path) \
		new_out = open(path, O_WRONLY | O_CREAT, 0664);\
		old_out = dup(1); \
		dup2(new_out, 1);

#define STOP_REDIRECT \
		dup2(old_out, 1); \
		close(new_out); \
		close(old_out);

#define DO_TEST(line, format, ...) \
		g_test_count++; \
		do { \
			system("rm -rf "FT_PRINTF_FILE); \
			system("rm -rf "LIBC_PRINTF_FILE); \
			char *_format = strdup(format); \
			int	new_out; \
			int	old_out; \
			int	returns[2]; \
			REDIRECT("user_output.txt") \
			returns[0] = ft_printf(format, ##__VA_ARGS__); \
			STOP_REDIRECT \
			REDIRECT("libc_output.txt") \
			returns[1] = printf(format, ##__VA_ARGS__); \
			fflush(stdout); \
			STOP_REDIRECT \
			printf("\033[1mTEST \033[96m#%08d\033[0m: \033[97m%s", g_test_count, format); \
			fflush(stdout); \
			compare(_format, line, returns[0], returns[1]); \
			free(_format); \
		} while (0);

int		g_test_count = 0;
int		g_test_count_passed = 0;
//usleep(1000 * 50); \

void	compare(char *format, int line, int libc_return, int ft_return)
{
	int		code;

	code = system("diff "FT_PRINTF_FILE" "LIBC_PRINTF_FILE" > /dev/null");
	if (code == 0 && (libc_return == ft_return))
	{
		g_test_count_passed++;
		printf("\033[90G%s\033[94G\033[0;32m %s\033[0m\033[0m\n", "✅", "SUCCESS");
		fflush(stdout);
	}
	else
	{
		printf("\033[90G%s\033[94G\033[0;32m %s, cause: %s, test at line %d\033[0m\033[0m\n", "❌", "DIFF", (libc_return == ft_return) ? "CONTENT" : "RETURN", line);
		fflush(stdout);
		exit(1);
	}
}

void	do_tests(void)
{
	// TEST HERES
}

int		main(int argc, char **argv)
{
	do_tests();
	printf("Final score: %d/%d\n", g_test_count_passed, g_test_count);
	fflush(stdout);
	while (1) ;
}
