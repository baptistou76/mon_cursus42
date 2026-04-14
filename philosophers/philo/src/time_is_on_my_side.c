/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_is_on_my_side.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:07:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/20 11:02:07 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	got_the_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	time_sleep(long long time, t_philo *philo)
{
	long long	i;

	i = got_the_time();
	while (!(is_philo_dead(philo->data)))
	{
		if (time_diff(i, got_the_time()) >= time)
			break ;
		usleep(50);
	}
}
