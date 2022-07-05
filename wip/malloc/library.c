/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:48:53 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 18:48:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <pthread.h>
#include <errno.h>

#include "ft.h"
#include "malloc.h"

#define ERRNO_ZERO() errno = 0;
#define ERRNO_SAVE() int error = errno;
#define ERRNO_RESTORE() errno = error;

#define TUNER_GET() const tunes_t *tunes = tune_get();

#define LOG_START(color_string, params, ...) \
		if (tunes->log) \
		{ \
			const char *color = tunes->log_colored ? color_string : ""; \
			ft_printf("%s%s(" params "): ", color, __FUNCTION__, __VA_ARGS__); \
		}

#define LOG_END_RESULT(result) \
		if (tunes->log) \
		{ \
			const char *color = tunes->log_colored ? COLOR_RESET : ""; \
			ft_printf("%p%s\n", result, color); \
		}

#define LOG_END_VOID() \
	if (tunes->log) \
	{ \
		const char *color = tunes->log_colored ? COLOR_RESET : ""; \
		ft_printf("<void>%s\n", color); \
	}

static pthread_mutex_t g_malloc_lock = PTHREAD_MUTEX_INITIALIZER;

static void
lock_acquire(const char *caller)
{
	int err = pthread_mutex_lock(&g_malloc_lock);

	if (err)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": could not acquire the lock: ", 2);
		ft_putstr_fd(strerror(err), 2);
		ft_putstr_fd("\n", 2);
		abort();
	}
}

static void
lock_release(const char *caller)
{
	int err = pthread_mutex_unlock(&g_malloc_lock);

	if (err)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": could not release the lock: ", 2);
		ft_putstr_fd(strerror(err), 2);
		ft_putstr_fd("\n", 2);
		abort();
	}
}

#define LOCK_ACQUIRE() lock_acquire(__FUNCTION__)
#define LOCK_RELEASE() lock_release(__FUNCTION__)

void*
malloc(size_t size)
{
	LOCK_ACQUIRE();

	TUNER_GET();

	LOG_START(COLOR_GREEN, "size=%l", size);

	ERRNO_ZERO();

	void *result = malloc_impl(__FUNCTION__, size);

	ERRNO_SAVE();

	LOG_END_RESULT(result);

	LOCK_RELEASE();

	ERRNO_RESTORE();

	return (result);
}

void
free(void *ptr)
{
	LOCK_ACQUIRE();

	TUNER_GET();

	LOG_START(COLOR_YELLOW, "ptr=%p", ptr);

	ERRNO_ZERO();

	free_impl(__FUNCTION__, ptr);

	ERRNO_SAVE();

	LOG_END_VOID();

	LOCK_RELEASE();

	ERRNO_RESTORE();
}

void*
realloc(void *ptr, size_t size)
{
	LOCK_ACQUIRE();

	TUNER_GET();

	LOG_START(COLOR_BLUE, "ptr=%p, size=%l", ptr, size);

	ERRNO_ZERO();

	void *result = realloc_impl(__FUNCTION__, ptr, size);

	ERRNO_SAVE();

	LOG_END_RESULT(result);

	LOCK_RELEASE();

	ERRNO_RESTORE();

	return (result);
}

void*
calloc(size_t nmemb, size_t size)
{
	LOCK_ACQUIRE();

	TUNER_GET();

	LOG_START(COLOR_PURPLE, "nmemb=%l, size=%l", nmemb, size);

	ERRNO_ZERO();

	void *result = calloc_impl(__FUNCTION__, nmemb, size);

	ERRNO_SAVE();

	LOG_END_RESULT(result);

	LOCK_RELEASE();

	ERRNO_RESTORE();

	return (result);
}

void*
reallocarray(void *ptr, size_t nmemb, size_t size)
{
	LOCK_ACQUIRE();

	TUNER_GET();

	LOG_START(COLOR_CYAN, "ptr=%p, nmemb=%l, size=%l", ptr, nmemb, size);

	ERRNO_ZERO();

	void *result = reallocarray_impl(__FUNCTION__, ptr, nmemb, size);

	ERRNO_SAVE();

	LOG_END_RESULT(result);

	LOCK_RELEASE();

	ERRNO_RESTORE();

	return (result);
}

void
show_alloc_mem()
{
	LOCK_ACQUIRE();

	ERRNO_ZERO();

	show_alloc_mem_impl();

	ERRNO_SAVE();

	LOCK_RELEASE();

	ERRNO_RESTORE();
}
