/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:28 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 18:40:57 by obastug          ###   ########.fr       */
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
			philosopher_loop, philos + (i));
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

	if (init_table(&table, argc, argv) == 1)
		return (1);
	if (init_philosophers(&philos, table) == 1)
		return (free_table(table), 1);
	start_philosophers(philos, table);
}
