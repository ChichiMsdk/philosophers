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

int	main(int argc, char **argv)
{
	t_rules		*rules;
	t_philo		**philo;
	t_timeval	timeval;
	int			i;

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
	cleaner(philo, rules);
	return (0);
}
