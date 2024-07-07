/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:21:23 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 14:22:50 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	p_take_silverware(t_philo *p)
{
	if (p->fork_r == p->fork_l)
	{
		pthread_mutex_lock(p->fork_r);
		philo_says(p, "has taken a fork");
		ft_usleep(p->philo_sim->time_to_die + 2);
		return ;
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
}

void	p_eat(t_philo *p)
{
	pthread_mutex_lock(&p->lock);
	gettimeofday(&p->last_meal, NULL);
	philo_says(p, "is eating");
	pthread_mutex_unlock(&p->lock);
	ft_usleep(p->philo_sim->time_to_eat);
	pthread_mutex_lock(&p->lock);
	p->no_meals++;
	pthread_mutex_unlock(&p->lock);
}

void	p_drop_silverware(t_philo *p)
{
	pthread_mutex_unlock(p->fork_r);
	pthread_mutex_unlock(p->fork_l);
}

void	p_sleep(t_philo *p)
{
	philo_says(p, "is sleeping");
	ft_usleep(p->philo_sim->time_to_sleep);
}

void	p_think(t_philo *p)
{
	int	think_ms;

	philo_says(p, "is thinking");
	if (p->philo_sim->number_of_philosophers % 2 == 0)
		think_ms = 0;
	else
		think_ms = p->philo_sim->time_to_eat * 2 - p->philo_sim->time_to_sleep;
	if (think_ms > 0)
		ft_usleep(think_ms);
}