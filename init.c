/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:09:34 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/20 17:09:34 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_philo	**init_philo(t_rules *rules, t_philo **philo, t_timeval *timeval)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo *) * rules->number_of_phil);
	if (!philo)
		return (NULL);
	while (i < rules->number_of_phil)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
		{
			free(philo);
			return (NULL);
		}
		philo[i]->timeval = timeval;
		philo[i]->current_time = 0;
		philo[i]->start_time = 0;
		philo[i]->is_dead = 0;
		philo[i]->is_eating = 0;
		philo[i]->is_sleeping = 0;
		philo[i]->id = i;
		init_mutex_thread(philo[i]);
		i++;
	}
	return (philo);
}

t_rules	*init_rules(t_rules *rules, char **argv)
{
	int	*converted;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	converted = convert_all(argv, converted);
	if (!converted)
		return (NULL);
	rules->number_of_phil = ft_atoi(argv[1]);
	rules->time_to_die = converted[0];
	rules->time_to_eat = converted[1]; 
	rules->time_to_sleep = converted[2];
	free(converted);
	return (rules);
}

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

void	*action_philo(void *arg)
{
	t_philo *philo;

	pthread_mutex_lock(&philo->mutex);
	philo = (t_philo *)arg;
	printf("Im philo[%d] and locked it !\n", philo->id);
	usleep(100);
	pthread_mutex_unlock(&philo->mutex);
	return NULL;
}

t_philo	*init_mutex_thread(t_philo *philo)
{
	pthread_mutex_init(&philo->mutex, NULL);
	pthread_create(&philo->th, NULL, action_philo, philo);
	return (philo);
}
