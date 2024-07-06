/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:47:09 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/06 23:44:42 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_satiated(t_philo *p)
{
	pthread_mutex_lock(&p->lock);
	if (p->philo_sim->number_of_times_each_philosopher_must_eat > 0
		&& p->no_meals >= p->philo_sim->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&p->lock);
		return (1);
	}
	pthread_mutex_unlock(&p->lock);
	return (0);
}

int	has_starved(t_philo *p)
{
	pthread_mutex_lock(&p->lock);
	if (time_since(p->last_meal) > p->philo_sim->time_to_die)
	{
		philo_says(p, "died");
		pthread_mutex_lock(&p->philo_sim->lock);
		p->philo_sim->stop = 1;
		pthread_mutex_unlock(&p->philo_sim->lock);
		pthread_mutex_unlock(&p->lock);
		return (1);
	}
	pthread_mutex_unlock(&p->lock);
	return (0);
}

int	sim_should_end(t_philo_sim *ps)
{
	int	i;
	int	full;

	i = 0;
	full = 1;
	while (i < ps->number_of_philosophers)
	{
		// printf(" %lld -- \n", gettime(philos[i].last_meal));
		if (has_starved(&ps->philos[i]))
			return (1);
		if (!is_satiated(&ps->philos[i]))
			full = 0;
		i++;
	}
	if (full)
	{
		pthread_mutex_lock(&ps->lock);
		ps->stop = 1;
		pthread_mutex_unlock(&ps->lock);
		return (1);
	}
	return (0);
}

void	monitor(t_philo_sim *philo_sim)
{
	while (!is_stop(philo_sim))
	{
		if (sim_should_end(philo_sim))
		{
			// pthread_mutex_unlock(&philo_sim->lock);
			return ;
		}
	}
}
