/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:11:41 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/19 19:11:41 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_rules *rules, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < rules->number_of_phil)
	{
		free(philo[i]);
		i++;
	}
	free(rules);
	free(philo);
}

static int	ft_isspace(char c)
{
	if (c == 32)
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				sign;
	long int		result;
	long int		tmp;

	sign = 1;
	result = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		tmp = result;
		result = (result * 10) + (*str - 48);
		str++;
		if (result < tmp && sign == 1)
			return (-1);
		if (result < tmp && sign == -1)
			return (0);
	}
	return ((int)result * sign);
}
