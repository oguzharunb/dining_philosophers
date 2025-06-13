/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:08:38 by obastug           #+#    #+#             */
/*   Updated: 2025/06/13 16:33:35 by obastug          ###   ########.fr       */
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
void	philosopher_eat(t_philo *philo)
{
	unsigned long	start_ms;

	if (philo->table->number_of_ph == 1 && if_one_fork(philo, philo->left_fork))
		return ;
	if (fork_taker(philo->left_fork, philo->right_fork, philo))
		return ;
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
	give_away_forks(philo);
	return ;
}

void	*philosopher_loop(void *args)
{
	t_philo	*philo;

	philo = args;
	while (1)
	{
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		if (!philo->table->philos_alive)
			return (pthread_mutex_unlock(&philo->table->philos_alive_lock)
				, args);
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		philosopher_eat(philo);
		if (philo->table->must_eat != -1 && philo->has_eaten
			>= philo->table->must_eat)
			return (args);
		if (!life_of_philos(philo->table))
			return (args);
		philosopher_sleep(philo);
		if (!life_of_philos(philo->table))
			return (args);
		philosopher_think(philo);
	}
	return (args);
}
