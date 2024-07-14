/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:21:23 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/14 14:36:54 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

int	p_take_silverware(t_philo *p)
{
	if (p->fork_r == p->fork_l)
	{
		pthread_mutex_lock(p->fork_r);
		philo_says(p, "has taken a fork");
		ft_smart_sleep(p->philo_sim->time_to_die + 5, p->philo_sim);
		return (1);
	}
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->fork_l);
		philo_says(p, "has taken a fork");
		pthread_mutex_lock(p->fork_r);
		philo_says(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->fork_r);
		philo_says(p, "has taken a fork");
		pthread_mutex_lock(p->fork_l);
		philo_says(p, "has taken a fork");
	}
	return (is_stop(p->philo_sim));
}

int	p_eat(t_philo *p)
{
	pthread_mutex_lock(&p->lock);
	gettimeofday(&p->last_meal, NULL);
	philo_says(p, "is eating");
	pthread_mutex_unlock(&p->lock);
	if (ft_smart_sleep(p->philo_sim->time_to_eat, p->philo_sim))
		return (1);
	pthread_mutex_lock(&p->lock);
	p->meals++;
	pthread_mutex_unlock(&p->lock);
	return (is_stop(p->philo_sim));
}

int	p_drop_silverware(t_philo *p)
{
	pthread_mutex_unlock(p->fork_r);
	if (p->fork_r != p->fork_l)
		pthread_mutex_unlock(p->fork_l);
	return (is_stop(p->philo_sim));
}

int	p_sleep(t_philo *p)
{
	philo_says(p, "is sleeping");
	if (ft_smart_sleep(p->philo_sim->time_to_sleep, p->philo_sim))
		return (1);
	return (is_stop(p->philo_sim));
}

int	p_think(t_philo *p)
{
	int	think_ms;

	philo_says(p, "is thinking");
	if (p->philo_sim->nbr_of_philos % 2 == 0)
		think_ms = 0;
	else
		think_ms = p->philo_sim->time_to_eat * 2 - p->philo_sim->time_to_sleep;
	if (think_ms > 0)
		ft_smart_sleep(p->philo_sim->time_to_eat, p->philo_sim);
	return (is_stop(p->philo_sim));
}
