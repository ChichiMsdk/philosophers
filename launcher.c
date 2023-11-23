/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:57:27 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/23 20:57:27 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*launch_th(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_create(&philo->ow_th, NULL, launch_ow, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->rules->write);
		if (*philo->flag == 1)
		{
			pthread_mutex_unlock(&philo->rules->write);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->write);
	}
	action_philo(philo);
	return (NULL);
}

void	*launch_ow(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->rules->write);
		if (*philo->flag == 1)
		{
			pthread_mutex_unlock(&philo->rules->write);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->write);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->rules->write);
		if (philo->start_time != 0)
		{
			pthread_mutex_unlock(&philo->rules->write);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->write);
	}
	overwatch_action(philo);
	return (NULL);
}
