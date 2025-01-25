/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:10:59 by obastug           #+#    #+#             */
/*   Updated: 2025/01/25 16:10:17 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	kill_all_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
	{
		pthread_detach((table->philos + i)->thread);
		i++;
	}
}

void	*did_philo_died(void *args)
{
	t_philo	*philo;
	static int i = 0;

	philo = args;
	while (i < 1000)
	{
		usleep(1000);
		i++;
	}
	kill_all_philos(philo->table);
	return args;
	//while (1)
	//{
	//	if ((get_current_ms(philo->table) - philo->last_meal_ms)
	//			> philo->table->time_to_die)
	//		{
	//			report_status(philo, DEATH);
	//			
	//		}
	//	usleep(1000);
	//}
}
