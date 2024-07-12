/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:57:27 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 19:22:35 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

long long	time_since(struct timeval tv_start)
{
	struct timeval	tv_now;

	gettimeofday(&tv_now, NULL);
	return ((tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000) - (tv_start.tv_sec
			* 1000 + tv_start.tv_usec / 1000));
}

int	ft_smart_sleep(int ms, t_philo_sim *ps)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	while (time_since(tv) < ms - 100)
	{
		if (is_stop(ps))
			return (1);
		usleep(50000);
	}	
	while (time_since(tv) < ms)
		usleep(10);
	return (0);
}

void	ft_sleep(int ms)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	while (time_since(tv) < ms)
		usleep(10);
}

// void	ft_sleep(int ms)
// {
// 	usleep(ms);
// }