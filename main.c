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
#include <pthread.h>
#include <sys/time.h>

void	printing_all(t_rules *rules, t_philo **philo)
{
	printf("number_of_phil: %d \n", rules->number_of_phil);
	printf("time_to_die: %d\n", rules->time_to_die);
	printf("time_to_eat: %d\n", rules->time_to_eat);
	printf("time_to_sleep: %d\n", rules->time_to_sleep);
	printf("is_dead ? %d\n", philo[0]->is_dead);
	printf("is_eating ? %d\n", philo[0]->is_eating);
	printf("is_sleeping ? %d\n", philo[0]->is_sleeping);
}

void	*im_thread(void *arg)
{
	printf("Im just a thread\n");
	return (NULL);
}

void	*im_thread2(void *arg)
{
	printf("Im just a thread2\n");
	return NULL;
}


int	main(int argc, char **argv)
{
	t_rules				*rules;
	t_philo				**philo;
	t_timeval			timeval;
	int					i;
	pthread_t			thread;
	pthread_t			thread2;
	pthread_mutex_t		mutex;

	if (argc != 5 && argc != 6)
	{
		printf("Wrong number of args\n");
		return (1);
	}
	rules = init_rules(rules, argv);
	if (!rules)
		return (-1);
	philo = init_philo(rules, philo, &timeval);
	if (!philo)
		return (-1);
	philo = init_mutex(philo, rules);
	init_mutex_thread(philo, rules);
//	printing_all(rules, philo);
	cleaner(philo, rules);
	return (0);
}
