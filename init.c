/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:26:03 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 18:41:51 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

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
