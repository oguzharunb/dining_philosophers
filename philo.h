/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:15:02 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 18:10:45 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

# define THINKING 0

typedef struct s_table
{
	pthread_mutex_t		report_lock;
	struct timeval		tv;
	struct timezone		*tz;
	int					number_of_ph;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	t_table			*table;
}	t_philo;

void	report_status(t_philo *philo, int status_code);

int		ft_atoi(char const *s);
int		ft_strlen(char const *s);

void	*philosopher_loop(void *args);
void	*philosopher_think(void *args);

int		throw_error(char const *s, int errno);
#endif