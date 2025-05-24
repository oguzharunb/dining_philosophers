/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:28 by obastug           #+#    #+#             */
/*   Updated: 2025/03/19 21:57:38 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	start_interrogator(t_philo *philos, int i)
{
	pthread_create(&(philos + i)->interrogator, NULL,
	did_philo_died, philos + i);
}

void	start_philosophers(t_philo *philos, t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (i < table->number_of_ph)
	{
		start_interrogator(philos, i);
		pthread_create(&(philos + i)->thread, NULL,
		philosopher_loop, philos + i);
		printf("philo %d started\n", (philos + i)->order);
		i++;
	}
	j = 0;
	while (j < i)
	{
		pthread_join((philos + (j))->thread, NULL);
		j++;
	}
}

void	join_philos(t_table *table)
{
	int	i;

	i = 0;
	while (table->)
}

int	main(int argc, char const **argv)
{
	t_philo			*philos;
	t_table			*table;
	t_fork			*forks;

	if (init_table(&table, argc, argv) == 1)
		return (1);
	if (init_philosophers(&philos, table) == 1)
		return (free_table(table), 1);
	if (init_forks(&forks, table) == 1)
		return (free_table(table), 1);
	put_forks_on_table(forks, philos, table);
	start_philosophers(philos, table);
	free_interrogators(table);
	free_table(table);
	free(philos);
	free(forks);
	return (0);
}
