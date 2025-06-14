/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:59 by obastug           #+#    #+#             */
/*   Updated: 2025/06/14 14:40:44 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	did_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_current_ms(philo->table)
		- philo->last_meal_ms > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	did_all_philos_have_eaten(t_table *table)
{
	int	i;

	i = 0;
	if (table->must_eat == -1)
		return (0);
	while (i < table->number_of_ph)
	{
		if (table->must_eat != -1
			&& table->philos[i].has_eaten < table->must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	philo_fed_enough(t_philo *philo)
{
	if (philo->table->must_eat != -1
		&& philo->has_eaten == philo->table->must_eat)
		return (1);
	return (0);
}

void	*interrogator(void *args)
{
	t_table		*table;
	int			i;

	table = args;
	while (!table->start_table)
		;
	while (1)
	{
		pthread_mutex_lock(&table->philos_alive_lock);
		if (table->philos_alive == 0)
			return (pthread_mutex_unlock(&table->philos_alive_lock), NULL);
		pthread_mutex_unlock(&table->philos_alive_lock);
		i = 0;
		while (i < table->number_of_ph)
		{
			if (did_all_philos_have_eaten(table))
				return (NULL);
			if (did_philo_died(table->philos + i))
				return (report_status(table->philos + i, DEATH), NULL);
			i++;
		}
		usleep(40);
	}
	return (NULL);
}
