/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:46:58 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 00:10:29 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <memory.h>   // memset()
# include <pthread.h>  // POSIX threads
# include <stdbool.h>  // booleans
# include <stdio.h>    // printf()
# include <stdlib.h>   // malloc(), free()
# include <sys/time.h> // gettimeofday()
# include <unistd.h>   // usleep(), write()

# define ALIVE 0
# define DEAD 1
# define FULL 2

typedef struct s_philo	t_philo;

typedef struct s_philo_sim
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					stop;
	struct timeval		tv_start;
	pthread_mutex_t		lock;
	pthread_mutex_t		start;
	pthread_mutex_t		write;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_philo_sim;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		lock;
	t_philo_sim			*philo_sim;
	struct timeval		last_meal;
	int					state;
	int					no_meals;
}						t_philo;

// utils/ft_atoi.c
int						ft_atoi(const char *nptr);

// debug.c
void					print_philo_sim(t_philo_sim philo_sim);

// philo.c
int						init_philos(t_philo_sim *philo_sim);
int						is_stop(t_philo_sim *ps);

// monitor.c
void					monitor(t_philo_sim *philo_sim);

// utils/time.c
long long				timestamp(void);
void					ft_usleep(int ms);
long long				time_since(struct timeval tv_start);

void					philo_says(t_philo *philo, char *msg);

#endif