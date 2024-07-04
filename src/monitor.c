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

void	monitor(t_philo_sim *philo_sim)
{
	int		i;
	t_philo	*philos;
	int		full;

	philos = philo_sim->philos;
	while (philo_sim->dead == 0)
	{
		i = 0;
		full = 0;
		while (i < philo_sim->number_of_philosophers)
		{
			// printf(" %lld -- \n", gettime(philos[i].last_meal));
			if (gettime(philos[i].last_meal) > philo_sim->time_to_die)
			{
				philo_says(philos[i], " has died");
				philo_sim->dead = 1;
				break ;
			}
			if (philos[i].no_meals >= philo_sim->number_of_times_each_philosopher_must_eat)
				full++;
			i++;
		}
		if (full == philo_sim->number_of_philosophers && philo_sim->number_of_times_each_philosopher_must_eat >= 0)
			philo_sim->dead = 1;
	}
}
