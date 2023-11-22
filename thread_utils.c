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

void	alert(t_philo *philo, char *alert)
{
	if (philo->rules->stop != 0)
	{
		if (alert[0] == 'd' || philo->rules->stop == 1)
		{
			printf("%ldms| %d %s\n", get_time(philo, philo->begin_simu),
				philo->id, alert);
			philo->rules->stop = 2;
			pthread_mutex_unlock(&philo->left_mutex);
			pthread_mutex_unlock(philo->right_mutex);
		}
		return ;
	}
	printf("%ldms| %d %s\n", get_time(philo, philo->begin_simu), philo->id,
		alert);
}

void	*overwatch(void *arg)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)arg;
	i = 0;
	while (1)
	{
		if (i >= philo[0]->rules->number_of_phil)
			i = 0;
		if (is_time_out(philo[i], philo[i]->rules->time_to_die) == 1)
		{
			philo[i]->rules->stop = 1;
			alert(philo[i], D);
			break ;
		}
		i++;
	}
	return (NULL);
}

void	cleaner(t_philo **philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_phil)
	{
		pthread_mutex_destroy(&philo[i]->left_mutex);
		i++;
	}
	free_all(rules, philo);
}
