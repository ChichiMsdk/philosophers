/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 01:55:22 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/22 01:55:22 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_time(t_philo *philo, long time)
{
	if (current_time(philo, 0) - time >= philo->rules->time_to_die)
	{
		philo->is_dead = 1;
		alert_ow(philo, "died");
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo, int meals)
{
	if (meals != 0 && philo->meals_eaten == meals)
	{
		pthread_mutex_lock(&philo->rules->write);
		philo->rules->stop = 1;
		alert_ow(philo, "ate");
		pthread_mutex_unlock(&philo->rules->write);
		return (1);
	}
	return (0);
}

void	*overwatch_action(t_philo *philo)
{
	int	meals;

	meals = philo->rules->number_meals;
	while (1)
	{
		pthread_mutex_lock(&philo->rules->eating);
		if (check_meals(philo, meals))
		{
			pthread_mutex_unlock(&philo->rules->eating);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->eating);
		pthread_mutex_lock(&philo->rules->write);
		if (check_time(philo, philo->start_time))
		{
			pthread_mutex_unlock(&philo->rules->write);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->write);
		usleep(10000);
	}
	return (NULL);
}

int	alert(t_philo *philo, char *alert)
{
	pthread_mutex_lock(&philo->rules->write);
	if (philo->rules->stop == 1)
	{
		pthread_mutex_unlock(&philo->rules->write);
		return (1);
	}
	if (philo->is_dead == 1)
	{
		if (ft_strcmp("died", alert) == 0 && philo->rules->stop == 0)
			printf("%ldms| %d %s\n", get_time(philo, philo->rules->begin_simu),
				philo->id, alert);
		philo->rules->stop = 1;
		pthread_mutex_unlock(&philo->rules->write);
		return (1);
	}
	printf("%ldms| %d %s\n", get_time(philo, philo->rules->begin_simu),
		philo->id, alert);
	pthread_mutex_unlock(&philo->rules->write);
	return (0);
}

void	alert_ow(t_philo *philo, char *alert)
{
	if (ft_strcmp("died", alert) == 0 && philo->rules->stop == 0)
	{
		printf("%ldms| %d %s\n", get_time(philo, philo->rules->begin_simu),
			philo->id, alert);
		philo->rules->stop = 1;
	}
	return ;
}
