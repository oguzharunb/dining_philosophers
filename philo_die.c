/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:59 by obastug           #+#    #+#             */
/*   Updated: 2025/06/13 15:11:07 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

int	did_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (get_current_ms(philo->table) - philo->last_meal_ms > philo->table->time_to_die)
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
		pthread_mutex_lock(&table->philos[i].eat_count_lock);
		if (table->must_eat != -1
			&& table->philos[i].has_eaten < table->must_eat)
		{
			pthread_mutex_unlock(&table->philos[i].eat_count_lock);	
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].eat_count_lock);
		i++;
	}
	return (1);
}

//if philosopher ate enough returns 1 or else 0
int	philo_fed_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_count_lock);
	if (philo->table->must_eat != -1
		&& philo->has_eaten == philo->table->must_eat)
	{
		pthread_mutex_unlock(&philo->eat_count_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_count_lock);
	return (0);
}

int	control_exit(t_table *table, int i)
{
	if (did_all_philos_have_eaten(table))
		return (1);
	if (!philo_fed_enough(table->philos + i)
		&& did_philo_died(table->philos + i))
		{
			report_status(table->philos + i, DEATH);
			return (1);
		}
	return (0);
}

void	*interrogator(void *args)
{
	t_table		*table;
	int			i;

	table = args;
	while (1)
	{
		pthread_mutex_lock(&table->philos_alive_lock);
		if (table->philos_alive == 0)
		{
			pthread_mutex_unlock(&table->philos_alive_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&table->philos_alive_lock);
		i = 0;
		while (i < table->number_of_ph)
		{
			if (control_exit(table, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
