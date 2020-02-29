/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:19:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:19:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <errno.h>
# include <string.h>
# include <sys/time.h>

# define IN 0
# define OUT 1
# define ERR 2

# define PROGRAM "philo_one"
# define NBR_OF_PARAMETER 5

typedef enum	e_man_state
{
	none = 0,
	sleeping = 1,
	thinking = 2,
	took_a_fork = 3,
	eating = 4,
	dead = 5
}				t_man_state;

typedef struct	s_param
{
	int		nbr_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_must_eat;
}				t_param;

typedef struct	s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}				t_fork;

typedef struct	s_man
{
	int				id;
	t_fork			*fork_l;
	t_fork			*fork_r;
	t_man_state		state;
	struct s_man	*next;
	pthread_t		thr_id;
	long			last_meal;
	long			eat_count;
	int				running;
	t_param			*param;
}				t_man;

typedef	void	*(*t_routine)(void *);

char			**g_parameters;
char			**g_man_states;

pthread_mutex_t	g_status_update_mutex;
int				g_someone_is_dead;

int				err_print_usage(void);
int				err_param_not_int(int param);
int				err_must_be_at_least_1_philo(void);
int				err_pthread(int err, int for_mutex);

int				x_atoi(char *str, int *err);
void			x_putstr(char *str);
void			x_putstr_fd(char *str, int fd);
void			x_putnbr(long n);
void			x_putnbr_fd(long n, int fd);
size_t			x_strlen(char *str);
void			*x_memset(void *buf, int c, size_t len);
long			x_millis(void);

int				philosophers_run(t_param param);

t_man			*philosophers_create(int *index);
t_man			*philosophers_destroy(t_man *man);

void			philosophers_monitor(t_man *root);

t_man			*philosophers_ring_create(t_param param);
void			philosophers_ring_attach_param(t_man *root, t_param *param);
int				philosophers_ring_destroy(t_man *root);
int				philosophers_ring_threader(t_man *root);
int				philosophers_ring_wait(t_man *root);

int				philosophers_ring_start(t_man *root);
int				philosophers_ring_end(t_man *root, t_man *to_kill);

void			philosophers_status_update(t_man *man, t_man_state new_state);

void			philosophers_routine(t_man *man);

int				philosophers_ring_forks(t_man *root);

t_fork			*fork_create(int *err);
t_fork			*fork_destroy(t_fork *fork);

int				fork_grab(t_fork *fork);
int				fork_release(t_fork *fork);

void			philosophers_debug_print_ring(t_man *root);

void			philosophers_status_mutex_destroy(void);
void			philosophers_status_mutex_init(void);

#endif
