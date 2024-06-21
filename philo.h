/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:46:58 by aprevrha          #+#    #+#             */
/*   Updated: 2024/06/21 13:28:05 by aprevrha         ###   ########.fr       */
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


typedef struct s_philo t_philo;

typedef struct s_philo_sim
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead;
    struct timeval	tv_start;
    t_philo         *philos;
}					t_philo_sim;

typedef struct s_philo
{
	int				id;
    pthread_t       thread;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_philo_sim		*philo_sim;
    struct timeval	last_meal;
    int             no_meals;
}					t_philo;

// utils/ft_atoi.c
int					ft_atoi(const char *nptr);

// debug.c
void				print_philo_sim(t_philo_sim philo_sim);

// philo.c
int					init_philos(t_philo_sim *philo_sim, pthread_mutex_t *forks);

#endif