/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:47:09 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/04 18:24:57 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_satiated(t_philo *p)
{

			pthread_mutex_lock(&p->lock);
			if (p->philo_sim->number_of_times_each_philosopher_must_eat > 0 && p->no_meals >= p->philo_sim->number_of_times_each_philosopher_must_eat)
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

			printf("%lld --- ", time_since(p->last_meal));
			if (time_since(p->last_meal) > p->philo_sim->time_to_die)
			{
				printf("%lld --- ", time_since(p->last_meal));
				philo_says(p, " has died");
				pthread_mutex_lock(&p->philo_sim->write);
				pthread_mutex_lock(&p->philo_sim->lock);
				p->philo_sim->dead = 1;
				pthread_mutex_unlock(&p->lock);
				return (1);
			}
			pthread_mutex_unlock(&p->lock);
			return (0);
}

int sim_should_end(t_philo_sim *ps)
{
	int		i;
	int		full;

	i = 0;
	full = 0;
	while (i < ps->number_of_philosophers)
	{
		// printf(" %lld -- \n", gettime(philos[i].last_meal));
			if (has_starved(&ps->philos[i]))
				return (1);
			if (is_satiated(&ps->philos[i]))
				full++;
			i++;
	}
	if (full == ps->number_of_philosophers)
		return (1);
	return (0);
}

void	monitor(t_philo_sim *philo_sim)
{
	while (philo_sim->dead == 0)
	{
		if (sim_should_end(philo_sim))
		{
			pthread_mutex_unlock(&philo_sim->lock);
			return ;
		}
	}
}
