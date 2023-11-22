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

t_rules	*init_rules(t_rules *rules, char **argv)
{
	int	*converted;

	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	converted = convert_all(argv, converted);
	if (!converted)
		return (NULL);
	pthread_mutex_init(&rules->write, NULL);
	rules->number_of_phil = ft_atoi(argv[1]);
	rules->time_to_die = converted[0];
	rules->time_to_eat = converted[1];
	rules->time_to_sleep = converted[2];
	rules->first_dead = 0;
	rules->stop = 0;
	free(converted);
	if (rules->number_of_phil < 1 || rules->time_to_die < 1
		|| rules->time_to_eat < 1 || rules->time_to_sleep < 1)
	{
		free(rules);
		return (NULL);
	}
	return (rules);
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
		pthread_mutex_init(&philo[i]->left_mutex, NULL);
		philo[i]->id = i + 1;
		philo[i]->timeval = timeval;
		philo[i]->current_time = 0;
		philo[i]->start_time = 0;
		philo[i]->is_dead = 0;
		i++;
	}
	return (philo);
}

t_philo	**init_mutex(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_phil)
	{
		if (i + 1 == rules->number_of_phil)
		{
			philo[i]->right_mutex = &philo[0]->left_mutex;
			i++;
			continue ;
		}
		if (i < rules->number_of_phil)
			philo[i]->right_mutex = &philo[i + 1]->left_mutex;
		i++;
	}
	return (philo);
}

t_philo	*init_mutex_thread(t_philo **philo, t_rules *rules)
{
	pthread_t	overwatch_th;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	while (i < rules->number_of_phil)
	{
		philo[i]->write = &philo[0]->rules->write;
		philo[i]->rules = rules;
		philo[i]->flag = &flag;
		pthread_create(&philo[i]->th, NULL, launch_th, philo[i]);
		i++;
	}
	pthread_create(&overwatch_th, NULL, overwatch, philo);
	flag = 1;
	pthread_join(overwatch_th, NULL);
	i = 0;
	while (i < rules->number_of_phil)
	{
		pthread_join(philo[i]->th, NULL);
		i++;
	}
	return (*philo);
}
