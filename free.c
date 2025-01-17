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

void	free_all_philosophers(t_philo *philos, int philo_number)
{
	(void)philos;
	(void)philo_number;
	return ;
}

void	free_all_forks(t_fork *forks, int fork_number)
{
	int	i;

	i = 0;
	while (i < fork_number)
	{
		pthread_mutex_destroy(&(forks + i)->mutex);
		i++;
	}
}
