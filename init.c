/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:26:03 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 19:17:03 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

// return 1 if all arguments is in right format, on error 0 is returned. 
int	is_arguments_right(int argc, char const **argv)
{
	if (argc != 2)
		return (throw_error("using: philo <number of philosophers>\n", 1));
	return (0);
}

// return 1 on error
int	init_table(t_table **table, int argc, char const **argv)
{
	if (is_arguments_right(argc, argv) == 1)
		return (1);
	*table = malloc(sizeof(t_table));
	if (!*table)
		return (throw_error("Memory error!\n", 1));
	pthread_mutex_init(&((*table)->report_lock), NULL);
	(*table)->number_of_ph = ft_atoi(argv[1]);
	return (0);
}

// returns 1 on error
int	init_forks(t_fork **forks, t_table *table)
{
	int	i;

	(*forks) = malloc(sizeof(t_fork) * table->number_of_ph);
	if (!*forks)
		return (throw_error("Memory Error!\n", 1));
	i = 0;
	while (i < table->number_of_ph)
	{
		pthread_mutex_init(&((*forks) + i)->mutex, NULL);
		i++;
	}
	return (0);
}

int	put_forks_on_table(t_fork *forks, t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_ph)
	{
		(philos + i)->left_fork = forks + min(i, (i + 1) % table->number_of_ph);
		(philos + i)->right_fork = forks + max(i, (i + 1) % table->number_of_ph);
		i++;
	}
}

int	init_philosophers(t_philo **philos, t_table *table)
{
	int	i;

	(*philos) = malloc(sizeof(t_philo) * table->number_of_ph);
	if (!*philos)
		return (throw_error("Memory Error\n", 1));
	i = 0;
	while (i < table->number_of_ph)
	{
		((*philos) + i)->table = table;
		i++;
	}
}
