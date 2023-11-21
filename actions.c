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

void	*action_philo_alone(void *arg)
{
	t_philo	*philo;
	int	id;

	philo = (t_philo *)arg;
	id = philo->id;
	pthread_mutex_lock(&philo->mutex);
	printf("Im philo[%d] and locked it !\n", id);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

void	*action_philo(t_philo *philo)
{
	set_time(philo, &philo->begin_simu);
	while(1)
	{
		set_time(philo, &philo->start_time);
		if (is_time_out(philo, philo->rules->time_to_die) == 1)
			return (NULL);
		pthread_mutex_lock(&philo->mutex);
		printf("%ld %d has taken a fork\n", get_time(philo, philo->begin_simu),
				philo->id);
		pthread_mutex_lock(philo->right_mutex);
		printf("%ld %d has taken a fork\n", get_time(philo, philo->begin_simu),
				philo->id);
		if (is_time_out(philo, philo->rules->time_to_die) == 1)
			break;
		printf("%ld %d is eating\n",get_time(philo, philo->begin_simu),
				philo->id);
		set_time(philo, &philo->start_time);
		usleep(philo->rules->time_to_eat);
		if (is_time_out(philo, philo->rules->time_to_die) == 1)
			break;
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(&philo->mutex);
		printf("%ld %d is sleeping\n",get_time(philo, philo->begin_simu),
				philo->id);
		usleep(philo->rules->time_to_sleep);
	}
	return (NULL);
}

void	*launch_th(void *arg)
{
	t_philo	*philo;
	t_philo	*tmp;
	int	id;
	int	*flag;

	philo = (t_philo *)arg;
	while (*philo->flag == 0)
	{
	}
	action_philo(philo);
	return (NULL);
}

void	cleaner(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_phil)
	{
		pthread_join(philo[i]->th, NULL);
		i++;
	}
	i = 0;
	while (i < rules->number_of_phil)
	{
		pthread_mutex_destroy(&philo[i]->mutex);
		i++;
	}
	free_all(rules, philo);
}
