/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obastug <obastug@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:25:30 by obastug           #+#    #+#             */
/*   Updated: 2025/01/17 18:10:26 by obastug          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char const *s)
{
	long	ret;

	ret = 0;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			ret = ret * 10 + ((*s) - '0');
		else
			return (0);
		s++;
	}
	return (ret);
}

int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
