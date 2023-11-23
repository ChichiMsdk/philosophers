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
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define A "ate"
# define F "has taken a fork"
# define T "is thinking"
# define S "is sleeping"
# define E "is eating"
# define D "died"

typedef struct timeval	t_timeval;

typedef struct t_philo
{
	pthread_t			th;
	pthread_t			ow_th;
	pthread_mutex_t		*write;
	pthread_mutex_t		*time;
	pthread_mutex_t		*eating;
	pthread_mutex_t		*right_mutex;
	pthread_mutex_t		*left_mutex;
	int					*flag;
	int					forks_left;
	int					forks_right;
	int					meals_eaten;
	int					is_dead;
	int					id;
	long				start_time;
	long				current_time;
	long				begin_simu;
	struct t_rules		*rules;
}						t_philo;

typedef struct t_rules
{
	pthread_t			th;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
	pthread_mutex_t		eating;
	pthread_mutex_t		time;
	long				begin_simu;
	int					stop;
	int					number_of_phil;
	int					number_meals;
	long				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_rules;

t_philo					**init_philo(t_rules *rules, t_philo **philo);
t_rules					*init_rules(t_rules *rules, char **argv);
t_philo					*init_mutex_thread(t_philo **philo, t_rules *rules);
t_philo					**init_mutex(t_philo **philo, t_rules *rules);
void					free_all(t_rules *rules, t_philo **philo);

int						ft_usleep(long time);
void					*set_time_current(t_philo *philo, long *time);
long					current_time(t_philo *philo, long time);
long					get_time(t_philo *philo, long time);
int						convert_time(char *argv);
int						*convert_all(char **argv, int *converted);

int						is_time_out(t_philo *philo, long limit_time);
long					set_time(t_philo *philo, long time);

void					*launch_ow(void *arg);
void					*overwatch_action(t_philo *philo);
int						alert(t_philo *philo, char *alert);
void					*launch_th(void *arg);
void					cleaner(t_philo **philo, t_rules *rules);
void					*action_philo(t_philo *philo);
void					*action_philo_alone(void *arg);
int						ft_atoi(const char *str);
void					alert_ow(t_philo *philo, char *alert);
int						ft_strcmp(const char *s1, const char *s2);
#endif
