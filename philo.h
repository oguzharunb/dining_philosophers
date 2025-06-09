/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:15:02 by obastug           #+#    #+#             */
/*   Updated: 2025/06/10 01:54:48 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define THINKING 0
# define SLEEPING 1
# define EATING 2
# define DEATH 3
# define LEFT_FORK_TAKEN 4
# define RIGHT_FORK_TAKEN 5

typedef struct s_philo	t_philo;

// must_eat is optional
typedef struct s_table
{
	pthread_mutex_t		report_lock;
	pthread_mutex_t		philos_alive_lock;
	pthread_t			interrogator;
	t_philo				*philos;
	struct timeval		tv;
	struct timezone		*tz;
	time_t				beginning_sec;
	suseconds_t			beginning_usec;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	int					must_eat;
	int					number_of_ph;
	int					philos_alive;
}	t_table;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		meal_lock;
	t_fork				*left_fork;
	t_fork				*right_fork;
	int					has_eaten;
	unsigned long		last_meal_ms;
	t_table				*table;
	int					order;
}	t_philo;

void	free_all_forks(t_fork *forks, int fork_number);
void	free_all_philosophers(t_philo *philos, int philo_number);
void	free_table(t_table *table);
void	free_interrogators(t_table *table);

int		init_philosophers(t_philo **philos, t_table *table);
int		init_table(t_table **table, int argc, char const **argv);
int		init_forks(t_fork **forks, t_table *table);
int		put_forks_on_table(t_fork *forks, t_philo *philos, t_table *table);
int		did_philo_died(t_philo *philo);
void	*interrogator(void *args);
int		life_of_philos(t_table *table);

void	report_status(t_philo *philo, int status_code);

int		ft_atoi(char const *s);
int		ft_strlen(char const *s);
int		max(int a, int b);
int		min(int a, int b);

void	*philosopher_loop(void *args);

void	init_time(t_table *table);
long	get_current_ms(t_table *table);
long	get_begin_ms(t_table *table);

int		throw_error(char const *s, int errno);
#endif