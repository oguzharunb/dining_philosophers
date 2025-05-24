/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:22:31 by obastug           #+#    #+#             */
/*   Updated: 2025/03/19 21:36:41 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	report_status(t_philo *philo, int status_code)
{
	long	ms;

	pthread_mutex_lock(&philo->table->report_lock);
	if (!philo->table->philos_alive)
		return ;
	ms = get_current_ms(philo->table);
	if (status_code == THINKING)
		printf("%ld %d is thinking\n", ms, philo->order);
	else if (status_code == SLEEPING)
		printf("%ld %d is sleeping\n", ms, philo->order);
	else if (status_code == EATING)
		printf("%ld %d is eating\n", ms, philo->order);
	else if (status_code == LEFT_FORK_TAKEN || status_code == RIGHT_FORK_TAKEN)
		printf("%ld %d has taken a fork\n", ms, philo->order);
	else if (status_code == DEATH)
		printf("%ld %d died\n", ms, philo->order);
	pthread_mutex_unlock(&philo->table->report_lock);
}
