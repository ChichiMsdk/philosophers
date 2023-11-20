/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmoussa <chmoussa@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:02:07 by chmoussa          #+#    #+#             */
/*   Updated: 2023/11/19 19:02:07 by chmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <sys/_types/_useconds_t.h>
# include <sys/_types/_timeval.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <semaphore.h>

typedef struct timeval	t_timeval;

typedef struct t_philo
{
	pthread_t		th;
	pthread_mutex_t mutex;
	int				is_eating;
	int				is_dead;
	int				is_sleeping;
	int				id;
	long			start_time;
	long			current_time;
	long			delta_time;
	struct timeval	*timeval;
}t_philo;

typedef struct t_rules
{
	int	number_of_phil;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}t_rules;

t_philo		**init_philo(t_rules *rules, t_philo **philo, t_timeval *timeval);
t_rules		*init_rules(t_rules *rules, char **argv);
t_philo		*init_mutex_thread(t_philo **philo, t_rules *rules);
void		free_all(t_rules *rules, t_philo **philo);

int			convert_time(char *argv);
int			*convert_all(char **argv, int *converted);
int			is_time_out(t_philo *philo, int limit_time);
int			convert_time(char *argv);
void		*set_time(t_philo *philo, long time);

int			ft_atoi(const char *str);
#endif
