/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:22:31 by obastug           #+#    #+#             */
/*   Updated: 2025/06/13 15:23:33 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	report_printer(int status_code, long ms, t_philo *philo)
{
	if (status_code == THINKING)
		printf("%ld %d is thinking\n", ms, philo->order);
	else if (status_code == SLEEPING)
		printf("%ld %d is sleeping\n", ms, philo->order);
	else if (status_code == EATING)
		printf("%ld %d is eating\n", ms, philo->order);
	else if (status_code == LEFT_FORK_TAKEN || status_code == RIGHT_FORK_TAKEN)
		printf("%ld %d has taken a fork\n", ms, philo->order);
}

void	report_status(t_philo *philo, int status_code)
{
	long	ms;

	pthread_mutex_lock(&philo->table->report_lock);
	pthread_mutex_lock(&philo->table->philos_alive_lock);
	if (!philo->table->philos_alive)
	{
		pthread_mutex_unlock(&philo->table->report_lock);
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->philos_alive_lock);
	ms = get_current_ms(philo->table);
	report_printer(status_code, ms, philo);
	if (status_code == DEATH)
	{
		pthread_mutex_lock(&philo->table->philos_alive_lock);
		philo->table->philos_alive = 0;
		pthread_mutex_unlock(&philo->table->philos_alive_lock);
		printf("%ld %d died\n", ms, philo->order);
		pthread_mutex_unlock(&philo->table->report_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->report_lock);
}
