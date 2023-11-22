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

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_mutex);
	if (is_time_out(philo, philo->rules->time_to_die) == 1)
		return ;
	alert(philo, F);
	pthread_mutex_lock(philo->right_mutex);
	if (is_time_out(philo, philo->rules->time_to_die) == 1)
		return ;
	alert(philo, F);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
	if (is_time_out(philo, philo->rules->time_to_die) == 1)
		return ;
	alert(philo, S);
	usleep(philo->rules->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	alert(philo, E);
	usleep(philo->rules->time_to_eat * 1000);
	if (is_time_out(philo, philo->rules->time_to_die) == 1)
		return ;
}

void	*action_philo(t_philo *philo)
{
	set_time(philo, &philo->begin_simu);
	set_time(philo, &philo->start_time);
	while (!philo->rules->stop)
	{
		alert(philo, T);
		take_forks(philo);
		if (is_time_out(philo, philo->rules->time_to_die) == 1)
		{
			pthread_mutex_unlock(&philo->left_mutex);
			pthread_mutex_unlock(philo->right_mutex);
			break ;
		}
		set_time(philo, &philo->start_time);
		eating(philo);
		if (is_time_out(philo, philo->rules->time_to_die) == 1)
		{
			pthread_mutex_unlock(&philo->left_mutex);
			pthread_mutex_unlock(philo->right_mutex);
			break ;
		}
		drop_forks(philo);
	}
	return (NULL);
}

void	*launch_th(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->flag == 0)
	{
	}
	action_philo(philo);
	return (NULL);
}
