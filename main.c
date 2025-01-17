/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:28 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 16:03:05 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

void	*philosopher_think(void *args)
{
	t_philo	*philo;

	philo = args;
	report_status(philo, THINKING);
	usleep(1000000);
	return (args);
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

void	init_table(t_table *table)
{
	pthread_mutex_init(&(table->report_lock), NULL);
}

int	main(void)
{
	unsigned long	number_of_ph;
	t_philo			*philos;
	t_table			*table;

	number_of_ph = 5;
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	philos = malloc(sizeof(t_philo) * number_of_ph);
	if (!philos)
		return (1);
	init_table(table);
	(philos + 0)->table = table;
	(philos + 1)->table = table;
	(philos + 2)->table = table;
	(philos + 3)->table = table;
	(philos + 4)->table = table;
	pthread_create(&(philos + 0)->thread, NULL, philosopher_loop, philos + 0);
	pthread_create(&(philos + 1)->thread, NULL, philosopher_loop, philos + 1);
	pthread_create(&(philos + 2)->thread, NULL, philosopher_loop, philos + 2);
	pthread_create(&(philos + 3)->thread, NULL, philosopher_loop, philos + 3);
	pthread_create(&(philos + 4)->thread, NULL, philosopher_loop, philos + 4);
	pthread_join((philos + 0)->thread, NULL);
	pthread_join((philos + 1)->thread, NULL);
	pthread_join((philos + 2)->thread, NULL);
	pthread_join((philos + 3)->thread, NULL);
	pthread_join((philos + 4)->thread, NULL);
}
