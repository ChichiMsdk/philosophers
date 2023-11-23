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

void	*set_time_current(t_philo *philo, long *time)
{
	struct timeval	timeval;
	if (gettimeofday(&timeval, NULL) == -1)
		return (NULL);
	*time = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (philo);
}

long	current_time(t_philo *philo, long time)
{
	struct timeval	timeval;

	(void)philo;
	gettimeofday(&timeval, NULL);
	time = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (time);
}

long	get_time(t_philo *philo, long time)
{
	long	get_timing;

	get_timing = 0;
	get_timing = current_time(philo, get_timing);
	get_timing -= time;
	return (get_timing);
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
	converted[0] = convert_time(argv[2]);
	converted[1] = convert_time(argv[3]);
	converted[2] = convert_time(argv[4]);
	if (argv[5])
	{
		converted[3] = convert_time(argv[5]);
		if (converted[3] <= 0)
			return (NULL);
	}
	else
		converted[3] = 0;
	while (i < 3)
	{
		if (converted[i] <= 0)
			return (NULL);
		i++;
	}
	return (converted);
}
