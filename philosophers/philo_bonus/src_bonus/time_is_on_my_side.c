/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_is_on_my_side.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:07:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/14 22:11:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	sem_wait(philo->data->write_lock);
	timestamp = got_the_time() - philo->data->start_time;
	printf("\033[0;32m%ld \033[0;31m%d \033[0;32m%s\033[0m\n", timestamp,
		philo->id, status);
	sem_post(philo->data->write_lock);
}
