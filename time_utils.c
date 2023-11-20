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
		if (converted[i] < 0)
			return (NULL);
		i++;
	}
	return (converted);
}

void	*set_time(t_philo *philo, long time)
{
	if (!philo || !philo->timeval)
		return (NULL);
	gettimeofday(philo->timeval, NULL);
	time = philo->timeval->tv_sec;
	return (philo);
}

int	is_time_out(t_philo *philo, int limit_time)
{
	long	delta_time;

	if (!philo || !philo->timeval || !philo->current_time 
		|| !philo->start_time)
		return (-1);
	delta_time = philo->current_time - philo->start_time;
	if (delta_time > limit_time)
		return (1);
	return (0);
}

int	convert_time(char *argv)
{
	int	time_converted;

	time_converted = ft_atoi(argv) * 1000; 
	return (time_converted);
}
