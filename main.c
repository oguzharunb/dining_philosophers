/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:28 by obastug           #+#    #+#             */
/*   Updated: 2025/03/19 21:41:21 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	start_philosophers(t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
	{
		pthread_create(&(philos + i)->thread, NULL,
			philosopher_loop, philos + i);
		pthread_create(&(philos + i)->interrogator, NULL,
			did_philo_died, philos + i);
		i++;
	}
	i = 0;
	while (i < table->number_of_ph)
	{
		pthread_join((philos + (i))->thread, NULL);
		i++;
	}
}

int	main(int argc, char const **argv)
{
	t_philo			*philos;
	t_table			*table;
	t_fork			*forks;

	if (init_table(&table, argc, argv) == 1)
		return (1);
	printf("table initialized\n");
	if (init_philosophers(&philos, table) == 1)
		return (free_table(table), 1);
		printf("philos initialized\n");
	if (init_forks(&forks, table) == 1)
		return (free_table(table), 1);
	printf("forks initialized\n");
	put_forks_on_table(forks, philos, table);
	printf("forks put on table\n");
	start_philosophers(philos, table);
	printf("philos were born\n");
	return (0);
}
