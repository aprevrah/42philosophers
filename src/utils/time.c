/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:57:27 by aprevrha          #+#    #+#             */
/*   Updated: 2024/07/07 14:33:45 by aprevrha         ###   ########.fr       */
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