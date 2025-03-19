/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:59 by obastug           #+#    #+#             */
/*   Updated: 2025/03/19 21:35:14 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	kill_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
	{
		//pthread_mutex_destroy(&(table->philos + i)->left_fork->mutex);
		i++;
	}
}

void	*did_philo_died(void *args)
{
	t_philo		*philo;
	static int	i = 0;

	philo = args;
	while (philo->table->philos_alive)
	{
		if ((get_current_ms(philo->table) - philo->last_meal_ms)
			> philo->table->time_to_die)
		{
			report_status(philo, DEATH);
			kill_all_philos(philo->table);
			return (args);
		}
		usleep(1000);
	}
}
