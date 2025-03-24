/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:34:51 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 18:44:10 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	free_table(t_table *table)
{
	pthread_mutex_destroy(&(table->report_lock));
	free(table);
}

void	free_interrogators(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
	{
		pthread_detach((table->philos + i)->interrogator);
		i++;
	}
}
