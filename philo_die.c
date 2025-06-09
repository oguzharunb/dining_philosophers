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

int		did_philo_died(t_philo *philo)
{
	if (get_current_ms(philo->table) - philo->last_meal_ms > philo->table->time_to_die)
		return (1);
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
			return (NULL);
		pthread_mutex_unlock(&table->philos_alive_lock);
		i = 0;
		while (i < table->number_of_ph)
		{
			pthread_mutex_lock(&table->philos_alive_lock);
			if (did_philo_died(table->philos + i))
			{
				report_status(table->philos + i, DEATH);
				table->philos_alive = 0;
				pthread_mutex_unlock(&table->philos_alive_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos_alive_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
