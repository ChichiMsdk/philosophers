/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:07:28 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/20 17:07:28 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	*set_time(t_philo *philo, long *time)
{
	if (!philo || !philo->timeval)
		return (NULL);
	gettimeofday(philo->timeval, NULL);
	*time = (philo->timeval->tv_sec * 1000) + (philo->timeval->tv_usec / 1000);
	return (philo);
}

long	get_time(t_philo *philo, long time)
{
	set_time(philo, &philo->current_time);
	return ((philo->current_time - time));
}

int	is_time_out(t_philo *philo, long limit_time)
{
	if (!philo || !philo->timeval || !philo->current_time || !philo->start_time)
		return (-1);
	if ((get_time(philo, philo->start_time)) >= limit_time)
	{
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

int	convert_time(char *argv)
{
	int	time_converted;

	time_converted = ft_atoi(argv);
	return (time_converted);
}

int	*convert_all(char **argv, int *converted)
{
	int	i;

	i = 0;
	converted = malloc(sizeof(int) * 3);
	if (!converted)
		return (NULL);
	converted[0] = convert_time(argv[2]);
	converted[1] = convert_time(argv[3]);
	converted[2] = convert_time(argv[4]);
	while (i < 3)
	{
		if (converted[i] <= 0)
			return (NULL);
		i++;
	}
	return (converted);
}
