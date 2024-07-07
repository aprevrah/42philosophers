/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:44:24 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 17:53:04 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parse_input(t_philo_sim *philo_sim, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("Wrong number of args\n"), 1);
	philo_sim->number_of_philos = ft_atoi(argv[1]);
	philo_sim->time_to_die = ft_atoi(argv[2]);
	philo_sim->time_to_eat = ft_atoi(argv[3]);
	philo_sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo_sim->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
		if (philo_sim->number_of_times_each_philo_must_eat < 1)
			return (printf("Positve integers only\n"), 1);
	}
	else
		philo_sim->number_of_times_each_philo_must_eat = -1;
	if (philo_sim->number_of_philos < 1 || philo_sim->number_of_philos > 300)
		return (printf("Min 1 philosophers, max 300 phlosophers\n"), 1);
	if (philo_sim->time_to_die < 1 || philo_sim->time_to_eat < 1
		|| philo_sim->time_to_sleep < 1)
		return (printf("Positve integers only\n"), 1);
	return (0);
}

void	mutex_err_silverware(pthread_mutex_t *forks, int nbr_of_mutexs)
{
	int	i;

	printf("Fork mutex initialization failed\n");
	i = 0;
	while (i < nbr_of_mutexs)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

pthread_mutex_t	*init_silverware(t_philo_sim *philo_sim)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(philo_sim->number_of_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < philo_sim->number_of_philos)
	{
		if (pthread_mutex_init(&(forks[i]), NULL) != 0)
			return (mutex_err_silverware(forks, i), NULL);
		i++;
	}
	return (forks);
}

int	init_sim(t_philo_sim *philo_sim)
{
	philo_sim->stop = 0;
	philo_sim->forks = init_silverware(philo_sim);
	if (!philo_sim->forks)
		return (1);
	if (pthread_mutex_init(&philo_sim->write, NULL) != 0)
		return (cleanup_forks(philo_sim), 1);
	if (pthread_mutex_init(&philo_sim->lock, NULL) != 0)
		return (pthread_mutex_destroy(&philo_sim->write),
			cleanup_forks(philo_sim), 1);
	gettimeofday(&philo_sim->tv_start, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo_sim	philo_sim;

	if (parse_input(&philo_sim, argc, argv))
		return (1);
	if (init_sim(&philo_sim))
		return (1);
	if (init_philos(&philo_sim))
		return (destroy_mutexs(&philo_sim), cleanup_forks(&philo_sim), 1);
	ft_usleep(10);
	monitor(&philo_sim);
	join_threads(&philo_sim, philo_sim.number_of_philos);
	cleanup_all(&philo_sim);
}
