/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/04 22:50:00 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
/* 
exit(t_philo_sim *philo_sim)
{
	int	i;

	i = 0;
	while (i < philo_sim->number_of_philosophers)
	{
		pthread_mutex_destroy(&philo_sim->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
}
 */
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
	pthread_mutex_t	*forks;

	philo_sim->dead = 0;
	pthread_mutex_lock(&philo_sim->start);
	forks = init_silverware(philo_sim);
	gettimeofday(&philo_sim->tv_start, NULL);
	init_philos(philo_sim, forks);
	return (0);
}

int	parse_input(t_philo_sim *philo_sim, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of args\n"), 1);
	pthread_mutex_init(&philo_sim->write, NULL);
	pthread_mutex_init(&philo_sim->start, NULL);
	pthread_mutex_init(&philo_sim->lock, NULL);
	pthread_mutex_lock(&philo_sim->lock);
	philo_sim->number_of_philosophers = ft_atoi(argv[1]);
	philo_sim->time_to_die = ft_atoi(argv[2]);
	philo_sim->time_to_eat = ft_atoi(argv[3]);
	philo_sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_sim->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		philo_sim->number_of_times_each_philosopher_must_eat = -1;
	pthread_mutex_unlock(&philo_sim->lock);
	if (philo_sim->number_of_philosophers < 1
		|| philo_sim->number_of_philosophers > 200)
		return (printf("Min 1 philosophers, max 200 phlosophers\n"), 1);
	if (philo_sim->time_to_die < 0 || philo_sim->time_to_eat < 0
		|| philo_sim->time_to_sleep < 0)
		return (printf("No negative input\n"), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_sim	philo_sim;

	if (parse_input(&philo_sim, argc, argv))
		return (1);
	setup(&philo_sim);
}
// no_philos, tt_die, tt_eat, tt_sleep, (max_eat)