/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/06/24 17:07:13 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

pthread_mutex_t	*init_silverware(t_philo_sim *philo_sim)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(philo_sim->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < philo_sim->number_of_philosophers)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
			printf("Mutex initialization failed\n");
		i++;
	}
	return (forks);
}

int	setup(t_philo_sim *philo_sim)
{
	pthread_mutex_t *forks;

    philo_sim->dead = 0;
	print_philo_sim(*philo_sim);
	forks = init_silverware(philo_sim);
    gettimeofday(&philo_sim->tv_start, NULL);
	init_philos(philo_sim, forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_sim	philo_sim;

	printf("Start\n");
	if (argc < 5)
	{
		printf("Too few args\n");
		return (1);
	}
	philo_sim.number_of_philosophers = ft_atoi(argv[1]);
	philo_sim.time_to_die = ft_atoi(argv[2]);
	philo_sim.time_to_eat = ft_atoi(argv[3]);
	philo_sim.time_to_sleep = ft_atoi(argv[4]);
	philo_sim.number_of_times_each_philosopher_must_eat = 0;
	if (argc > 5)
		philo_sim.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	setup(&philo_sim);
}
// no_philos, tt_die, tt_eat, tt_sleep, (max_eat)