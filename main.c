/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:28 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 17:21:35 by obastug          ###   ########.fr       */
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

void	init_table(t_table *table, int number_of_ph)
{
	pthread_mutex_init(&(table->report_lock), NULL);
	table->number_of_ph = number_of_ph;
}

void	init_philosophers(t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
	{
		(philos + i)->table = table;
		i++;
	}
}

void	start_philosophers(t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
		pthread_create(&(philos + i)->thread, NULL, philosopher_loop, philos + (i++));
	i = 0;
	while (i < table->number_of_ph)
		pthread_join((philos + (i++))->thread, NULL);
}

int	main(void)
{
	unsigned long	number_of_ph;
	t_philo			*philos;
	t_table			*table;

	number_of_ph = 4;
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	philos = malloc(sizeof(t_philo) * number_of_ph);
	if (!philos)
		return (1);
	init_table(table, number_of_ph);
	init_philosophers(philos, table);
	start_philosophers(philos, table);
}
