/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/05/07 17:00:32 by aprevrha         ###   ########.fr       */
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

int	setup(t_philo_sim *philo_sim)
{
	print_philo_sim(*philo_sim);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_sim philo_sim;

	if (argc < 4)
	{
		printf("Too few args\n");
		return (1);
	}
	philo_sim.number_of_philosophers = ft_atoi(argv[1]);
	philo_sim.time_to_die = ft_atoi(argv[2]);
	philo_sim.time_to_eat = ft_atoi(argv[3]);
	philo_sim.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		philo_sim.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	setup(&philo_sim);
}
