/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:59 by obastug           #+#    #+#             */
/*   Updated: 2025/03/19 22:08:06 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	kill_all_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->number_of_ph)
	{
		pthread_mutex_destroy(&(philo->table->philos + i)->left_fork->mutex);
		i++;
	}
	i = 0;
	while (i < philo->table->number_of_ph)
	{
		if (philo != philo->table->philos + i)
			pthread_detach((philo->table->philos + i)->thread);
		i++;
	}
}

void	*did_philo_died(void *args)
{
	t_philo		*philo;
	long	last_meal;
	
	philo = args;
	while (1)
	{
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		if (!philo->table->philos_alive)
		{
			pthread_mutex_unlock(&philo->table->philos_alive_lock);
			return (args);
		}
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		pthread_mutex_lock(&philo->meal_lock);
		last_meal = philo->last_meal_ms;
		pthread_mutex_unlock(&philo->meal_lock);
		if ((get_current_ms(philo->table) - last_meal)
			> philo->table->time_to_die)
		{
			report_status(philo, DEATH);
			philo->table->philos_alive = 0;
			return (args);
		}
		usleep(1000);
	}
}
