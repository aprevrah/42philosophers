/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:46:58 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/14 14:36:54 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>  // POSIX threads
# include <stdio.h>    // printf()
# include <stdlib.h>   // malloc(), free()
# include <sys/time.h> // gettimeofday()
# include <unistd.h>   // usleep()

typedef struct s_philo	t_philo;

typedef struct s_philo_sim
{
	int					nbr_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_of_times_each_philo_must_eat;
	int					stop;
	struct timeval		tv_start;
	pthread_mutex_t		lock;
	pthread_mutex_t		write;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_philo_sim;

typedef struct s_philo
{
	int					id;
	int					meals;
	struct timeval		last_meal;
	pthread_t			thread;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		lock;
	t_philo_sim			*philo_sim;
}						t_philo;

// utils/ft_atoi.c
int						ft_atoi(const char *nptr);

// philo.c
int						init_philos(t_philo_sim *philo_sim);
int						is_stop(t_philo_sim *ps);
void					philo_says(t_philo *philo, char *msg);

// monitor.c
void					monitor(t_philo_sim *philo_sim);

// utils/cleanup.c
void					cleanup_all(t_philo_sim *ps);
void					cleanup_forks(t_philo_sim *ps);
void					cleanup_philos(t_philo_sim *ps);
void					destroy_mutexs(t_philo_sim *ps);
void					join_threads(t_philo_sim *philo_sim,
							int nbr_of_threads);

// utils/philo_action.c
int						p_take_silverware(t_philo *p);
int						p_eat(t_philo *p);
int						p_drop_silverware(t_philo *p);
int						p_sleep(t_philo *p);
int						p_think(t_philo *p);

// utils/time.c
long long				time_since(struct timeval tv_start);
int						ft_smart_sleep(int ms, t_philo_sim *ps);
void					ft_sleep(int ms);

#endif