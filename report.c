/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:22:31 by obastug           #+#    #+#             */
/*   Updated: 2025/01/21 09:04:11 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	report_status(t_philo *philo, int status_code)
{
	long	ms;

	pthread_mutex_lock(&philo->table->report_lock);
	ms = get_current_ms(philo->table);
	if (status_code == THINKING)
		printf("(%ld) philo %p is thinking\n", ms, philo);
	else if (status_code == SLEEPING)
		printf("(%ld) philo %p is sleeping\n", ms, philo);
	else if (status_code == EATING)
		printf("(%ld) philo %p is eating\n", ms, philo);
	pthread_mutex_unlock(&philo->table->report_lock);
}
