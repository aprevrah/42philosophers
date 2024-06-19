/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/06/19 21:44:01 by aprevrha         ###   ########.fr       */
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

void	philo_says(t_philo philo, char *msg)
{
	printf("%lu %i %s\n", gettime(philo.philo_sim->tv_start), philo.id, msg);
}

void	take_silverware(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->fork_r);
		philo_says(*p, "has taken a fork");
		pthread_mutex_lock(p->fork_l);
		philo_says(*p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->fork_l);
		philo_says(*p, "has taken a fork");
		pthread_mutex_lock(p->fork_r);
		philo_says(*p, "has taken a fork");
	}
}

void	*thread_function(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (!p->philo_sim->dead)
	{
		take_silverware(p);
		philo_says(*p, " is eating");
		usleep((useconds_t)p->philo_sim->time_to_eat);
        gettimeofday((struct timeval *)(&(p->last_meal)), NULL);
		if (pthread_mutex_unlock(p->fork_r) || pthread_mutex_unlock(p->fork_l))
		{
			perror("pthread_mutex_unlock");
			p->philo_sim->dead = 1;
		}
		philo_says(*p, " is sleeping");
		usleep((useconds_t)p->philo_sim->time_to_sleep);
		philo_says(*p, " is thinking");
	}
	return (NULL);
}

void	monitor(t_philo_sim *philo_sim)
{
	int	i;
    t_philo *philos;

    philos = philo_sim->philos;
	while (philo_sim->dead == 0)
	{
        i = 0;
		while (i < philo_sim->number_of_philosophers)
        {
            if ((long)gettime(philos[i].last_meal) > philo_sim->time_to_die)
            {
                philo_says(philos[i], " has died");
                philo_sim->dead = 1;
                break ;
            }
		    i++;
        }
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
	//monitor(philo_sim);
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
