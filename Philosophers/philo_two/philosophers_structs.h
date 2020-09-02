/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_structs.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:44:38 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:44:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_STRUCTS_H
# define PHILOSOPHERS_STRUCTS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

typedef struct
{
	int	nbr_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_must_eat;
}		t_param;

typedef enum
{
	none = 0,
	sleeping = 1,
	thinking = 2,
	took_a_fork = 3,
	eating = 4,
	dead = 5
}	t_state;

typedef struct {
	sem_t		*sem;
	int			id;
	int			is;
	long		start;
	long		last_meal;
	long		eat_count;
	bool		stopped;
	pthread_t	thr;
	pthread_t	thr_monitor;
}	t_man;

typedef struct {
	t_man		*mans;
}	t_table;

typedef struct {
	t_table	*table;
	t_man	*man;
	int		index;
}	t_seat;

#endif
