/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:57:27 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 16:46:13 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

void	cleanup_forks(t_philo_sim *ps)
{
	int	i;

	i = 0;
	while (i < ps->number_of_philos)
	{
		pthread_mutex_destroy(&(ps->forks)[i]);
		i++;
	}
	free(ps->forks);
}

void	cleanup_philos(t_philo_sim *ps)
{
	int	i;

	i = 0;
	while (i < ps->number_of_philos)
	{
		pthread_mutex_destroy(&ps->philos[i].lock);
		i++;
	}
	free(ps->philos);
}

void	destroy_mutexs(t_philo_sim *ps)
{
	pthread_mutex_destroy(&ps->write);
	pthread_mutex_destroy(&ps->lock);
}

void	cleanup_all(t_philo_sim *ps)
{
	destroy_mutexs(ps);
	cleanup_forks(ps);
	cleanup_philos(ps);
}
