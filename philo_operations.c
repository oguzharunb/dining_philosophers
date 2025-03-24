/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:08:38 by obastug           #+#    #+#             */
/*   Updated: 2025/03/19 22:04:45 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// philosophers think for 10ms every time
void	philosopher_think(t_philo *philo)
{
	report_status(philo, THINKING);
	usleep(10000);
}

void	philosopher_sleep(t_philo *philo)
{
	long	start_ms;

	report_status(philo, SLEEPING);
	start_ms = get_current_ms(philo->table);
	while (get_current_ms(philo->table)
		- start_ms < philo->table->time_to_sleep)
		usleep(100);
}

void	philosopher_eat(t_philo *philo)
{
	long	start_ms;

	if (!philo->table->philos_alive)
		return ;
	pthread_mutex_lock(&philo->left_fork->mutex);
	if (!philo->table->philos_alive)
		return ;
	pthread_mutex_lock(&philo->right_fork->mutex);
	report_status(philo, EATING);
	start_ms = get_current_ms(philo->table);
	while (get_current_ms(philo->table) - start_ms < philo->table->time_to_eat)
		usleep(1000);
	philo->last_meal_ms = get_current_ms(philo->table);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	*philosopher_loop(void *args)
{
	t_philo	*philo;

	philo = args;
	while (1)
	{
		if (!philo->table->philos_alive)
			return (args);
		philosopher_eat(philo);
		if (!philo->table->philos_alive)
			return (args);
		philosopher_sleep(philo);
		if (!philo->table->philos_alive)
			return (args);
		philosopher_think(philo);
	}
}
