/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:50:40 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/09 16:51:04 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void print_philo_sim(t_philo_sim philo_sim)
{
	printf("number_of_philosophers %i\n", philo_sim.number_of_philosophers);
	printf("time_to_die %i\n", philo_sim.time_to_die);
	printf("time_to_eat %i\n", philo_sim.time_to_eat);
	printf("time_to_sleep %i\n", philo_sim.time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat %i\n", philo_sim.number_of_times_each_philosopher_must_eat);
}