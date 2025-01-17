/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:08:38 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 18:13:47 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	philosopher_think(t_philo *philo)
{
	report_status(philo, THINKING);
	usleep(1000000);
}

void	*philosopher_loop(void *args)
{
	t_philo	*philo;

	philo = args;
	while (1)
	{
		philosopher_think(philo);
	}
}
