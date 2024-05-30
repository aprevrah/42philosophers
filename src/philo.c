/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/30 20:18:55 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	gettime(struct timeval tv_start)
{
	struct timeval	tv_now;
	long			seconds;
	long			useconds;

	gettimeofday(&tv_now, NULL);
	seconds = tv_now.tv_sec - tv_start.tv_sec;
	useconds = tv_now.tv_usec - tv_start.tv_usec;
	return (seconds * 1000000 + useconds);
}

void    take_silverware(t_philo *p)
{
    if (p->id % 2 == 0)
    {
		pthread_mutex_lock(p->fork_r);
		printf("%lu %i has taken a fork\n", gettime(p->philo_sim->tv_start),
			p->id);
		pthread_mutex_lock(p->fork_l);
		printf("%lu %i has taken a fork\n", gettime(p->philo_sim->tv_start),
			p->id);
    }
    else
    {
		pthread_mutex_lock(p->fork_l);
		printf("%lu %i has taken a fork\n", gettime(p->philo_sim->tv_start),
			p->id);
		pthread_mutex_lock(p->fork_r);
		printf("%lu %i has taken a fork\n", gettime(p->philo_sim->tv_start),
			p->id);
    }
}

void	*thread_function(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->philo_sim->dead)
	{
        take_silverware(p);
		printf("%lu %i is eating\n", gettime(p->philo_sim->tv_start), p->id);
		usleep((useconds_t)p->philo_sim->time_to_eat);
		if (pthread_mutex_unlock(p->fork_r) || pthread_mutex_unlock(p->fork_r))
		{
			perror("pthread_mutex_unlock");
			p->philo_sim->dead = 1;
		}
		printf("%lu %i is sleeping\n", gettime(p->philo_sim->tv_start), p->id);
		usleep((useconds_t)p->philo_sim->time_to_sleep);
		printf("%lu %i is thinking\n", gettime(p->philo_sim->tv_start), p->id);
	}
	return (NULL);
}

void    monitor(t_philo_sim *ps)
{
    int i;
    i = 0;
    while (ps->dead == 0)
    {

        i++;
    }
}

int	init_philos(t_philo_sim *philo_sim, pthread_mutex_t *forks)
{
	int			i;
	pthread_t	philos[philo_sim->number_of_philosophers];
	t_philo		targs[philo_sim->number_of_philosophers];

	// philos = malloc(philo_sim->number_of_philosophers * sizeof(pthread_t));
	// if (!philos)
	// return (1);
	i = 0;
	while (i < philo_sim->number_of_philosophers)
	{
		targs[i].fork_r = &forks[i];
		if (i == philo_sim->number_of_philosophers - 1)
			targs[i].fork_l = &forks[0];
		else
			targs[i].fork_l = &forks[i + 1];
		targs[i].id = i;
		targs[i].philo_sim = philo_sim;
		if (pthread_create(&philos[i], NULL, thread_function,
				(void *)&targs[i]) != 0)
			printf("Thread initialization failed\n");
		// printf("philo %i\n", i);
		i++;
	}
    monitor(philo_sim);
	i = 0;
	while (i < philo_sim->number_of_philosophers)
	{
		pthread_join(philos[i], NULL);
		printf("philo %i has ended\n", i);
		i++;
	}
	// pthread_exit(NULL);
	printf("Philo sim Has Ended\n");
	return (0);
}
