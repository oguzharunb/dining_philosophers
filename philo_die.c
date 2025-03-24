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
	int	self;

	
	while (i < philo->table->number_of_ph)
	{
		pthread_mutex_destroy(&(philo->table->philos + i)->left_fork->mutex);
		pthread_detach((philo->table->philos + i)->thread);
		i++;
	}
}

void	*did_philo_died(void *args)
{
	t_philo		*philo;

	philo = args;
	while (philo->table->philos_alive)
	{
		if ((get_current_ms(philo->table) - philo->last_meal_ms)
			> philo->table->time_to_die)
		{
			report_status(philo, DEATH);
			kill_all_philos(philo);
			return (args);
		}
		usleep(100);
	}
}
