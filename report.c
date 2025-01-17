/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   report.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:22:31 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 17:13:27 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	report_status(t_philo *philo, int status_code)
{
	pthread_mutex_lock(&philo->table->report_lock);
	gettimeofday(&(philo->table->tv), NULL);
	if (status_code == THINKING)
	{
		printf("(%ld) philo %p is thinking\n", philo->table->tv.tv_sec, philo);
	}
	pthread_mutex_unlock(&philo->table->report_lock);
}
