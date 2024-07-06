/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:57:27 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 00:10:25 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"

// long long	timestamp(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// void	ft_usleep(int ms)
// {
// 	long int	time;

// 	time = timestamp();
// 	while (timestamp() - time < ms)
// 		usleep(ms / 10);
// }

// void	ft_usleep(int ms)
// {
// 	struct timeval	tv;
// 	struct timeval	now;

// 	gettimeofday(&tv, NULL);
// 	gettimeofday(&now, NULL);
// 	while ((now.tv_sec * 1000 + now.tv_usec / 1000) -
// 			(tv.tv_sec * 1000 + tv.tv_usec / 1000) < ms)
// 	{
// 		gettimeofday(&now, NULL);
// 		usleep(ms / 4);
// 	}
// }

// long long	time_since(struct timeval tv_start)
// {
// 	struct timeval	tv_now;
// 	long			seconds;
// 	long			useconds;

// 	gettimeofday(&tv_now, NULL);
// 	seconds = tv_now.tv_sec - tv_start.tv_sec;
// 	useconds = tv_now.tv_usec - tv_start.tv_usec;
// 	return (seconds * 1000 + useconds / 1000);
// }

long long	time_since(struct timeval tv_start)
{
	struct timeval	tv_now;

	gettimeofday(&tv_now, NULL);
	return ((tv_now.tv_sec * 1000 + tv_now.tv_usec / 1000) - (tv_start.tv_sec
			* 1000 + tv_start.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	while (time_since(tv) < ms)
		usleep(ms);
}

// void	ft_usleep(int ms)
// {
// 	usleep(ms);
// }