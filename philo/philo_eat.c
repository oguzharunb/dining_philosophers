/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:10:16 by obastug           #+#    #+#             */
/*   Updated: 2025/06/14 12:46:57 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

int	if_one_fork(t_philo *philo, t_fork *first_fork)
{
	pthread_mutex_lock(&first_fork->mutex);
	report_status(philo, LEFT_FORK_TAKEN);
	while (1)
	{
		if (!life_of_philos(philo->table))
			return (1);
		usleep(100);
	}
	return (0);
}

int	fork_taker(t_fork *first_fork, t_fork *second_fork, t_philo *philo)
{
	if (!life_of_philos(philo->table))
		return (1);
	pthread_mutex_lock(&first_fork->mutex);
	if (!life_of_philos(philo->table))
	{
		pthread_mutex_unlock(&first_fork->mutex);
		return (1);
	}
	report_status(philo, LEFT_FORK_TAKEN);
	pthread_mutex_lock(&second_fork->mutex);
	if (!life_of_philos(philo->table))
	{
		unlock_forks(philo);
		return (1);
	}
	report_status(philo, RIGHT_FORK_TAKEN);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_ms = get_current_ms(philo->table);
	pthread_mutex_unlock(&philo->meal_lock);
	report_status(philo, EATING);
	return (0);
}

void	give_away_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_ms = get_current_ms(philo->table);
	pthread_mutex_unlock(&philo->meal_lock);
	unlock_forks(philo);
	(philo->has_eaten)++;
}
