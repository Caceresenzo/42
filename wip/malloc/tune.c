/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tune.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:48:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/18 20:48:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#include "ft.h"
#include "malloc.h"

const tunes_t*
tune_get()
{
	static tunes_t tunes;
	static bool initialized = false;
	static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	if (!initialized)
	{
		pthread_mutex_lock(&lock);

		if (!initialized)
		{
			tune_initialize(&tunes);
			initialized = true;
		}

		pthread_mutex_unlock(&lock);
	}

	return (&tunes);
}

bool
tune_find_boolean(const char *key, bool default_value)
{
	char *value = getenv(key);

	if (value)
	{
		if (ft_strcasecmp("true", value) == 0 || ft_strcasecmp("1", value) == 0)
			return (true);

		if (strcasecmp("false", value) == 0 || ft_strcasecmp("0", value) == 0)
			return (false);
	}

	return (default_value);
}

void
tune_initialize(tunes_t *tunes)
{
	tunes->log = tune_find_boolean(TO_ENV_VAR_NAME("LOG"), false);
	tunes->log_colored = tune_find_boolean(TO_ENV_VAR_NAME("LOG_COLORED"), true);
	tunes->check_magic = tune_find_boolean(TO_ENV_VAR_NAME("CHECK_MAGIC"), true);
}