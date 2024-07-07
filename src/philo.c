/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 17:54:19 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_stop(t_philo_sim *ps)
{
	int	stop;

	pthread_mutex_lock(&ps->lock);
	stop = ps->stop;
	pthread_mutex_unlock(&ps->lock);
	return (stop);
}

void	philo_says(t_philo *philo, char *msg)
{
	if (is_stop(philo->philo_sim))
		return ;
	pthread_mutex_lock(&philo->philo_sim->write);
	printf("%lld %i %s\n", time_since(philo->philo_sim->tv_start), philo->id,
		msg);
	pthread_mutex_unlock(&philo->philo_sim->write);
}

void	*thread_function(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	pthread_mutex_lock(&p->lock);
	gettimeofday(&p->last_meal, NULL);
	pthread_mutex_unlock(&p->lock);
	if (p->id % 2 == 0)
		ft_usleep(p->philo_sim->time_to_eat / 4);
	while (1)
	{
		p_take_silverware(p);
		if (is_stop(p->philo_sim))
			return (p_drop_silverware(p), NULL);
		p_eat(p);
		p_drop_silverware(p);
		if (is_stop(p->philo_sim))
			return (NULL);
		p_sleep(p);
		if (is_stop(p->philo_sim))
			return (NULL);
		p_think(p);
	}
	return (NULL);
}

void	shutdown_sim(t_philo_sim *ps, int nbr_of_threads, int nbr_of_mutexs)
{
	int	i;

	pthread_mutex_lock(&ps->lock);
	ps->stop = 1;
	pthread_mutex_unlock(&ps->lock);
	join_threads(ps, nbr_of_threads);
	i = 0;
	while (i < nbr_of_mutexs)
	{
		pthread_mutex_destroy(&ps->philos[i].lock);
		i++;
	}
}

int	init_philos(t_philo_sim *philo_sim)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	forks = philo_sim->forks;
	philos = malloc(philo_sim->number_of_philos * sizeof(t_philo));
	if (!philos)
		return (1);
	i = 0;
	while (i < philo_sim->number_of_philos)
	{
		if (pthread_mutex_init(&philos[i].lock, NULL) != 0)
			return (shutdown_sim(philo_sim, i, i), 1);
		philos[i].id = i + 1;
		philos[i].philo_sim = philo_sim;
		philos[i].no_meals = 0;
		philos[i].fork_r = &forks[i];
		philos[i].fork_l = &forks[(i + 1) % philo_sim->number_of_philos];
		if (pthread_create(&philos[i].thread, NULL, thread_function,
				(void *)&philos[i]) != 0)
			return (shutdown_sim(philo_sim, i, i + 1), 1);
		i++;
	}
	philo_sim->philos = philos;
	return (0);
}
