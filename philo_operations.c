/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:08:38 by obastug           #+#    #+#             */
/*   Updated: 2025/06/12 12:43:15 by obastug          ###   ########.fr       */
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

int	lock_forks(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	return (1);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

//handle the case when there is just one philosopher
void	philosopher_eat(t_philo *philo)
{
	unsigned long	start_ms;
	t_fork			*first_fork;
	t_fork			*second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->table->number_of_ph == 1)
	{
		if (!lock_forks(first_fork))
			return ;
		report_status(philo, LEFT_FORK_TAKEN);
		while (1)
		{
			if (!life_of_philos(philo->table))
				return ;
			usleep(1000);
		}
	}
	if (philo->order % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (!life_of_philos(philo->table))
		return ;
	if (!lock_forks(first_fork))
		return ;
	if (!life_of_philos(philo->table))
		return ;
	report_status(philo, LEFT_FORK_TAKEN);
	if (!lock_forks(second_fork))
	{
		pthread_mutex_unlock(&first_fork->mutex);
		return ;
	}
	if (!life_of_philos(philo->table))
	{
		unlock_forks(philo);
		return ;
	}
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
	(philo->has_eaten)++;
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
			return (pthread_mutex_unlock(&philo->table->philos_alive_lock), args);
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		philosopher_eat(philo);
		if (philo->table->must_eat != -1 && philo->has_eaten >= philo->table->must_eat)
			return (args);
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		if (!philo->table->philos_alive)
			return (pthread_mutex_unlock(&philo->table->philos_alive_lock), args);
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		philosopher_sleep(philo);
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		if (!philo->table->philos_alive)
			return (pthread_mutex_unlock(&philo->table->philos_alive_lock), args);
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		philosopher_think(philo);
	}
	return (args);
}
