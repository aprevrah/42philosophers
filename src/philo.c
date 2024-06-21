/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/06/21 15:14:53 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}
long long	gettime(struct timeval tv_start)
{
	struct timeval	tv_now;
	long			seconds;
	long			useconds;

	gettimeofday(&tv_now, NULL);
	seconds = tv_now.tv_sec - tv_start.tv_sec;
	useconds = tv_now.tv_usec - tv_start.tv_usec;
	return (seconds * 1000 + useconds / 1000);
}

void	philo_says(t_philo philo, char *msg)
{
	printf("%lld %i %s\n", gettime(philo.philo_sim->tv_start), philo.id, msg);
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
		gettimeofday(&p->last_meal, NULL);
		philo_says(*p, " is eating");
        p->no_meals++;
		ft_usleep((useconds_t)p->philo_sim->time_to_eat);
		if (pthread_mutex_unlock(p->fork_r) || pthread_mutex_unlock(p->fork_l))
		{
			perror("pthread_mutex_unlock");
			p->philo_sim->dead = 1;
		}
		philo_says(*p, " is sleeping");
		ft_usleep((useconds_t)p->philo_sim->time_to_sleep);
		philo_says(*p, " is thinking");
	}
	return (NULL);
}

void	monitor(t_philo_sim *philo_sim)
{
	int		i;
	t_philo	*philos;
    int     full;

	philos = philo_sim->philos;
	while (philo_sim->dead == 0)
	{
		i = 0;
        full = 0;
		while (i < philo_sim->number_of_philosophers)
		{
			if ((long)gettime(philos[i].last_meal) > philo_sim->time_to_die)
			{
				philo_says(philos[i], " has died");
				philo_sim->dead = 1;
				break ;
			}
            if (philos[i].no_meals >= philo_sim->number_of_times_each_philosopher_must_eat)
                full++;
			i++;
		}
        if (full == philo_sim->number_of_philosophers)
            philo_sim->dead = 1;
	}
}

int	init_philos(t_philo_sim *philo_sim, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*philos;

	philos = malloc(philo_sim->number_of_philosophers * sizeof(t_philo));
	if (!philos)
		return (1);
	i = 0;
	while (i < philo_sim->number_of_philosophers)
	{
		philos[i].id = i;
        philos[i].philo_sim = philo_sim;
        philos[i].no_meals = 0;
        gettimeofday(&philos[i].last_meal, NULL);
        // forks
		philos[i].fork_r = &forks[i];
		if (i == philo_sim->number_of_philosophers - 1)
			philos[i].fork_l = &forks[0];
		else
			philos[i].fork_l = &forks[i + 1];
		if (pthread_create(&philos[i].thread, NULL, thread_function,
				(void *)&philos[i]) != 0)
			printf("Thread initialization failed\n");
		// printf("philo %i\n", i);
		i++;
	}
	philo_sim->philos = philos;
	monitor(philo_sim);
	i = 0;
	while (i < philo_sim->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		printf("philo %i has ended\n", i);
		i++;
	}
	// pthread_exit(NULL);
	printf("Philo sim Has Ended\n");
	return (0);
}
