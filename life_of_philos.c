/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 01:11:42 by obastug           #+#    #+#             */
/*   Updated: 2025/06/10 01:12:11 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life_of_philos(t_table *table)
{
	pthread_mutex_lock(&table->philos_alive_lock);
	if (!table->philos_alive)	
	{
		pthread_mutex_unlock(&table->philos_alive_lock);
		return (0);
	}
	pthread_mutex_unlock(&table->philos_alive_lock);
	return (1);
}
