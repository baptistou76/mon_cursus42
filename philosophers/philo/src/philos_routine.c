/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:17:21 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/26 15:35:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	data = philo->data;
	i = 0;
	while (!is_philo_dead(philo->data))
	{
		if (is_philo_dead(philo->data))
			break ;
		enjoy_your_meal(philo);
		if (is_philo_dead(philo->data))
			break ;
		print_philo(philo, "is sleeping\n");
		time_sleep(data->time_to_sleep, philo);
		if (is_philo_dead(philo->data))
			break ;
		print_philo(philo, "is thinking\n");
		i++;
	}
	return (NULL);
}

void	enjoy_your_meal(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	taking_forks(philo);
	eating_time(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_philo(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		print_philo(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_philo(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_philo(philo, "has taken a fork\n");
	}
}

// void	released_forks(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(philo->left_fork);
// 		pthread_mutex_unlock(philo->right_fork);
// 	}
// }

void	eating_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_eaten);
	print_philo(philo, "is eating\n");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = got_the_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_unlock(&philo->meal_eaten);
	time_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->meal_nb_mutex);
	philo->meal_nb++;
	pthread_mutex_unlock(&philo->meal_nb_mutex);
}
