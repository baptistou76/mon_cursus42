/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:11:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/14 22:16:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	usleep(100);
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	print_status(philo, "is eating");
	philo->last_meal = got_the_time();
	philo->meals_eaten++;
	usleep(philo->data->time_to_eat * 1000);
}

void	philo_sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void	philo_released_forks(t_philo *philo)
{
	print_status(philo, "is thinking");
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_reaper(t_philo *philo)
{
	sem_wait(philo->data->death_lock);
	if ((philo->data->meals_required != -1
			&& philo->meals_eaten >= philo->data->meals_required)
		|| philo->data->is_dead == true)
	{
		sem_post(philo->data->meals_done);
		philo_exiter(philo, 0);
	}
	sem_post(philo->data->death_lock);
}
