/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:15:02 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 19:20:23 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define THINKING 0
# define SLEEPING 1
# define EATING 2

typedef struct s_table
{
	pthread_mutex_t		report_lock;
	struct timeval		tv;
	struct timezone		*tz;
	int					number_of_ph;
}	t_table;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_table			*table;
}	t_philo;

void	free_all_forks(t_fork *forks, int fork_number);
void	free_all_philosophers(t_philo *philos, int philo_number);
void	free_table(t_table *table);

int		init_philosophers(t_philo **philos, t_table *table);
int		init_table(t_table **table, int argc, char const **argv);
int		init_forks(t_fork **forks, t_table *table);
int		put_forks_on_table(t_fork *forks, t_philo *philos, t_table *table);

void	report_status(t_philo *philo, int status_code);

int		ft_atoi(char const *s);
int		ft_strlen(char const *s);
int		max(int a, int b);
int		min(int a, int b);

void	*philosopher_loop(void *args);

int		throw_error(char const *s, int errno);
#endif