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

t_philo **init_mutex(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_phil)
	{
		if (i+1 == rules->number_of_phil)
		{
			philo[i]->right_mutex = philo[0]->mutex;
			philo[i]->left_mutex = philo[i-1]->mutex;
		}
		if (i-1 < 0)
		{
			philo[i]->right_mutex = philo[i+1]->mutex;
			philo[i]->left_mutex = philo[rules->number_of_phil-1]->mutex;
		}
		else
		{
			philo[i]->right_mutex = philo[i+1]->mutex;
			philo[i]->left_mutex = philo[i-1]->mutex;
		}
	}
	return (philo);
}

t_philo	**init_philo(t_rules *rules, t_philo **philo, t_timeval *timeval)
{
	int	i;
	pthread_t thread;

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
		pthread_mutex_init(&philo[i]->mutex, NULL);
		philo[i]->timeval = timeval;
		philo[i]->current_time = 0;
		philo[i]->start_time = 0;
		philo[i]->is_dead = 0;
		philo[i]->is_eating = 0;
		philo[i]->is_sleeping = 0;
		philo[i]->id = i;
		i++;
	}
	philo = init_mutex(philo, rules);
	init_mutex_thread(philo, rules);
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
	t_philo	*philo;
	t_philo	*tmp;
	int	id;

	id = philo->id;
	philo = (t_philo *)arg;
	if (id == 22)
		pthread_mutex_lock(&philo->mutex);
	if (id == 0)
		pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&philo->mutex);
	printf("Im philo[%d] and locked it !\n", id);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

t_philo	*init_mutex_thread(t_philo **philo, t_rules *rules)
{
	int	i;
	pthread_mutex_t	mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	while (i < rules->number_of_phil)
	{
		pthread_create(&philo[i]->th, NULL, action_philo, *philo);
		i++;
	}
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	i = 0;
	return (*philo);
}
