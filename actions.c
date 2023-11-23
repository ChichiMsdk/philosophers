/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:41:12 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/21 17:41:12 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lock_and_alert(t_philo *philo, pthread_mutex_t *fst,
		pthread_mutex_t *scd, char *code)
{
	pthread_mutex_lock(fst);
	if (alert(philo, code) || fst == scd)
	{
		pthread_mutex_unlock(fst);
		return (NULL);
	}
	pthread_mutex_lock(scd);
	if (alert(philo, code))
	{
		pthread_mutex_unlock(fst);
		pthread_mutex_unlock(scd);
		return (NULL);
	}
	return (philo);
}

void	*take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!lock_and_alert(philo, philo->right_mutex, philo->left_mutex, F))
			return (NULL);
	}
	else
	{
		if (!lock_and_alert(philo, philo->left_mutex, philo->right_mutex, F))
			return (NULL);
	}
	return (philo);
}

void	*drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_mutex);
	pthread_mutex_unlock(philo->left_mutex);
	if (alert(philo, S))
		return (NULL);
	usleep(philo->rules->time_to_sleep * 1000);
	return (philo);
}

void	*eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->eating);
	if (alert(philo, E))
	{
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(philo->left_mutex);
		pthread_mutex_unlock(&philo->rules->eating);
		return (NULL);
	}
	philo->meals_eaten++;
	pthread_mutex_lock(&philo->rules->write);
	set_time_current(philo, &philo->start_time);
	pthread_mutex_unlock(&philo->rules->eating);
	if (philo->rules->stop == 1)
	{
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(philo->left_mutex);
		pthread_mutex_unlock(&philo->rules->write);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->rules->write);
	usleep(philo->rules->time_to_eat * 1000);
	return (philo);
}

void	*action_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->rules->write);
	set_time_current(philo, &philo->start_time);
	pthread_mutex_unlock(&philo->rules->write);
	while (1)
	{
		if (alert(philo, T))
			break ;
		if (!take_forks(philo))
			break ;
		if (!eating(philo))
			break ;
		if (!drop_forks(philo))
			break ;
		usleep(10000);
	}
	return (NULL);
}
