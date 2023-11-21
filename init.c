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
			philo[i]->right_mutex = &philo[0]->mutex;
			i++;
			continue;
		}
		if (i-1 < 0)
		{
			philo[i]->right_mutex = &philo[i+1]->mutex;
			i++;
			continue;
		}
		if (i < rules->number_of_phil)
			philo[i]->right_mutex = &philo[i+1]->mutex;
		else
			return (philo);
		i++;
	}
	return (philo);
}

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
		pthread_mutex_init(&philo[i]->mutex, NULL);
		philo[i]->id = i;
		philo[i]->timeval = timeval;
		philo[i]->current_time = 0;
		philo[i]->start_time = 0;
		philo[i]->is_dead = 0;
		philo[i]->is_eating = 0;
		philo[i]->is_sleeping = 0;
		i++;
	}
	if ( rules->number_of_phil == 1)
	{

		pthread_create(&philo[0]->th, NULL, action_philo_alone, philo[0]);
		return (philo);
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
	if (rules->number_of_phil < 1 || rules->time_to_die < 1
		|| rules->time_to_eat < 1 || rules->time_to_sleep < 1)
	{
		free(rules);
		return (NULL);
	}
	return (rules);
}

void	*thread_block(void *arg)
{
	pthread_mutex_t	*mutex;

	mutex = (pthread_mutex_t *)arg;
	printf("Im thread_block and locked it !\n");
	return (NULL);
}

t_philo	*init_mutex_thread(t_philo **philo, t_rules *rules)
{
	int	i;
	pthread_mutex_t	mutex;
	pthread_t	thread;
	int flag = 0;
	i = 0;
	while (i < rules->number_of_phil)
	{
		philo[i]->rules = rules;
		philo[i]->flag = &flag;
		philo[i]->left_mutex = &mutex;
		pthread_create(&philo[i]->th, NULL, launch_th, philo[i]);
		i++;
	}
	flag = 1;
	return (*philo);
}
