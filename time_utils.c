/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:34:03 by obastug           #+#    #+#             */
/*   Updated: 2025/01/21 09:02:49 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_ms(t_table *table)
{
	gettimeofday(&table->tv, NULL);
	return (((table->tv.tv_sec - table->beginning_sec) * 1000)
				+ ((table->tv.tv_usec - table->beginning_usec) / 1000));
}

void	init_time(t_table *table)
{
	gettimeofday(&table->tv, NULL);
	table->beginning_sec = table->tv.tv_sec;
	table->beginning_usec = table->tv.tv_usec;
}

long	get_begin_ms(t_table *table)
{
	return (table->beginning_sec * 1000 + table->beginning_usec / 1000);
}