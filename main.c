/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:02:04 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/19 19:02:04 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	convert_time(char *argv)
{
	int	time_converted;

	time_converted = ft_atoi(argv) * 1000; 
	return (time_converted);
}

t_philo	**init_philo(t_rules *rules, t_philo **philo)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo*));
	*philo = malloc(sizeof(t_philo) * rules->number_of_phil);
	if (!philo)
		return (NULL);
	while (i < rules->number_of_phil)
	{
		philo[i]->is_dead = 0;
		philo[i]->is_eating = 0;
		philo[i]->is_sleeping = 0;
		i++;
	}
	return (philo);
}

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

void	printing_all(t_rules *rules, t_philo *philo)
{
	printf("number_of_phil: %d \n", rules->number_of_phil);
	printf("time_to_die: %d\n", rules->time_to_die);
	printf("time_to_eat: %d\n", rules->time_to_eat);
	printf("time_to_sleep: %d\n", rules->time_to_sleep);
	printf("is_dead ? %d\n", philo->is_dead);
	printf("is_eating ? %d\n", philo->is_eating);
	printf("is_sleeping ? %d\n", philo->is_sleeping);
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

int	main(int argc, char **argv)
{
	int					time;
	useconds_t			time_converted;
	t_rules				*rules;
	t_philo				**philo;

	time = 1000;
	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of args\n");
		return (1);
	}
	if (!init_rules(rules, argv))
		return (-1);
	rules = init_rules(rules, argv);
	if (!rules)
		return (-1);
	philo = init_philo(rules, philo);
	if (!philo)
		return (-1);
	printing_all(rules, *philo);
	free_all(rules, philo);
	return (0);
}
