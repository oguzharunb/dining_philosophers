/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:08:38 by obastug           #+#    #+#             */
/*   Updated: 2025/06/13 15:10:00 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// philosophers think for 10ms every time
void	philosopher_think(t_philo *philo)
{
	unsigned long	time_to_think;

	time_to_think = (philo->table->time_to_die - philo->table->time_to_eat
				- philo->table->time_to_sleep) / 2;
	report_status(philo, THINKING);
	while (1)
	{
		pthread_mutex_lock(&philo->meal_lock);
		if (get_current_ms(philo->table) - philo->last_meal_ms
			> time_to_think)
		{
			pthread_mutex_unlock(&philo->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		if (!philo->table->philos_alive)
		{
			pthread_mutex_unlock(&philo->table->philos_alive_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		usleep(1000);
	}
}

void	philosopher_sleep(t_philo *philo)
{
	unsigned long	start_ms;

	report_status(philo, SLEEPING);
	start_ms = get_current_ms(philo->table);
	while (get_current_ms(philo->table)
		- start_ms < philo->table->time_to_sleep)
	{
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		if (!philo->table->philos_alive)
		{
			pthread_mutex_unlock(&philo->table->philos_alive_lock);
			return ;
		}
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		usleep(1000);
	}
}

//handle the case when there is just one philosopher
void	philosopher_ate(t_philo *philo)
{
	unsigned long	start_ms;

	report_status(philo, RIGHT_FORK_TAKEN);
	report_status(philo, EATING);
	start_ms = get_current_ms(philo->table);
	while (get_current_ms(philo->table) - start_ms < philo->table->time_to_eat)
	{
		if (!life_of_philos(philo->table))
		{
			unlock_forks(philo);
			return ;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_ms = get_current_ms(philo->table);
	pthread_mutex_unlock(&philo->meal_lock);
	unlock_forks(philo);
	pthread_mutex_lock(&philo->eat_count_lock);
	(philo->has_eaten)++;
	pthread_mutex_unlock(&philo->eat_count_lock);
}

int	philosopher_eat(t_philo *philo)
{
	unsigned long	start_ms;

	if (philo->table->number_of_ph == 1)
	{
		if (!lock_forks(philo->right_fork))
			return (0);
		report_status(philo, LEFT_FORK_TAKEN);
		while (1)
		{
			if (!life_of_philos(philo->table))
				return (0);
			usleep(1000);
		}
	}
	if (!life_of_philos(philo->table))
		return (0);
	if (!lock_forks(philo->right_fork))
		return (0);
	if (!life_of_philos(philo->table))
		return (0);
	report_status(philo, LEFT_FORK_TAKEN);
	if (!lock_forks(philo->left_fork))
		return (pthread_mutex_unlock(&philo->right_fork->mutex));
	if (!life_of_philos(philo->table))
		return (unlock_forks(philo));
	philosopher_ate(philo);
	return (0);
}

void	*philosopher_loop(void *args)
{
	t_philo	*philo;

	philo = args;
	while (1)
	{
		if (!life_of_philos(philo->table))
			return (args);
		philosopher_eat(philo);
		pthread_mutex_lock(&philo->eat_count_lock);
		if (philo->table->must_eat != -1 && philo->has_eaten >= philo->table->must_eat)
		{
			pthread_mutex_lock(&philo->eat_count_lock);
			return (args);
		}
		pthread_mutex_unlock(&philo->eat_count_lock);
		if (!life_of_philos(philo->table))
			return (args);
		philosopher_sleep(philo);
		if (!life_of_philos(philo->table))
			return (args);
		philosopher_think(philo);
	}
	return (args);
}
