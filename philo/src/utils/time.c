/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:57:27 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/14 14:17:50 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"
#include <limits.h>

void	stop_sim(t_philo_sim *ps)
{
	pthread_mutex_lock(&ps->lock);
	ps->stop = 1;
	pthread_mutex_unlock(&ps->lock);
}

long long	time_since(struct timeval tv_start, t_philo_sim *ps)
{
	struct timeval	tv_now;

	if (gettimeofday(&tv_now, NULL) != 0)
		return (stop_sim(ps), LONG_MAX);
	return ((tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000) - (tv_start.tv_sec
			* 1000 + tv_start.tv_usec / 1000));
}

int	ft_smart_sleep(int ms, t_philo_sim *ps)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (stop_sim(ps), 0);
	while (time_since(tv, ps) < ms - 100)
	{
		if (is_stop(ps))
			return (1);
		usleep(50000);
	}
	while (time_since(tv, ps) < ms)
		usleep(10);
	return (0);
}

void	ft_sleep(int ms, t_philo_sim *ps)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		stop_sim(ps);
		return ;
	}
	while (time_since(tv, ps) < ms)
		usleep(10);
}

// void	ft_sleep(int ms)
// {
// 	usleep(ms);
// }