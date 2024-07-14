/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 19:22:35 by aprevrha         ###   ########.fr       */
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
		ft_smart_sleep(p->philo_sim->time_to_eat / 2, p->philo_sim);
	while (1)
	{
		if (p_take_silverware(p))
			return (p_drop_silverware(p), NULL);
		if (p_eat(p))
			return (p_drop_silverware(p), NULL);
		if (p_drop_silverware(p))
			break ;
		if (p_sleep(p))
			break ;
		if (p_think(p))
			break ;
		if (p->philo_sim->number_of_times_each_philo_must_eat >= 0 && p->no_meals >= p->philo_sim->number_of_times_each_philo_must_eat)
			break ;
	}
	return (NULL);
}

void	shutdown_sim(t_philo_sim *ps, int nbr_of_threads, int nbr_of_mutexs)
{
	int	i;

	pthread_mutex_lock(&ps->lock);
	ps->stop = 1;
	pthread_mutex_unlock(&ps->lock);
	usleep(100);
	join_threads(ps, nbr_of_threads);
	i = 0;
	while (i < nbr_of_mutexs)
	{
		pthread_mutex_destroy(&ps->philos[i].lock);
		i++;
	}
	free(ps->philos);
}

int	init_philos(t_philo_sim *ps)
{
	int	i;

	ps->philos = malloc(ps->number_of_philos * sizeof(t_philo));
	if (!ps->philos)
		return (1);
	i = 0;
	while (i < ps->number_of_philos)
	{
		if (pthread_mutex_init(&ps->philos[i].lock, NULL) != 0)
			return (shutdown_sim(ps, i, i), 1);
		gettimeofday(&ps->philos[i].last_meal, NULL);
		ps->philos[i].id = i + 1;
		ps->philos[i].philo_sim = ps;
		ps->philos[i].no_meals = 0;
		ps->philos[i].fork_r = &ps->forks[i];
		ps->philos[i].fork_l = &ps->forks[(i + 1) % ps->number_of_philos];
		if (pthread_create(&ps->philos[i].thread, NULL,
				thread_function, (void *)&ps->philos[i]) != 0)
			return (shutdown_sim(ps, i, i + 1), 1);
		i++;
	}
	return (0);
}
