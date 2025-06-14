/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:08:38 by obastug           #+#    #+#             */
/*   Updated: 2025/06/14 12:50:55 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// philosophers think for 10ms every time
void	philosopher_think(t_philo *philo)
{
	unsigned long	time_to_think;
	unsigned long	start_ms;

	start_ms = get_current_ms(philo->table);
	time_to_think = (philo->table->time_to_die - philo->table->time_to_eat
			- philo->table->time_to_sleep) / 2;
	report_status(philo, THINKING);
	if (time_to_think < 1)
		return ;
	while (get_current_ms(philo->table)
		- start_ms < time_to_think)
	{
		if (!life_of_philos(philo->table))
			return ;
		usleep(100);
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
		usleep(100);
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
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_ms = get_current_ms(philo->table);
	pthread_mutex_unlock(&philo->meal_lock);
	while (get_current_ms(philo->table) - start_ms < philo->table->time_to_eat)
	{
		if (!life_of_philos(philo->table))
		{
			unlock_forks(philo);
			return ;
		}
		usleep(100);
	}
	give_away_forks(philo);
	return ;
}

void	*philosopher_loop(void *args)
{
	t_philo	*philo;

	philo = args;
	while (!philo->table->start_table)
		;
	if (philo->order % 2 == 0)
		usleep(20);
	while (1)
	{
		if (!life_of_philos(philo->table))
			return (args);
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
