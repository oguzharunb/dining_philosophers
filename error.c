/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:39:35 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 17:49:47 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

// returns errno in all cases, writes given string to STDERR
int	throw_error(char const *s, int errno)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return (errno);
}
