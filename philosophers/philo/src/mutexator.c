/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:24:08 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/25 15:22:19 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deadly_mutex(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	t_philo	*current;

	philo = (t_philo *)arg;
	data = philo->data;
	current = philo;
	pthread_mutex_lock(&current->meal_eaten);
	pthread_mutex_lock(&current->last_meal_mutex);
	if (time_diff(current->last_meal, got_the_time()) > data->time_to_die)
	{
		print_philo(current, "died\n");
		set_philo_dead(philo->data, 1);
	}
	pthread_mutex_unlock(&current->last_meal_mutex);
	pthread_mutex_unlock(&(current->meal_eaten));
}

void	hungry_mutex(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)arg;
	data = philo->data;
	i = -1;
	while (data->meals_required != -1 && ++i < data->nb_philos)
	{
		pthread_mutex_lock(&philo->meal_nb_mutex);
		if (philo->meal_nb < data->meals_required)
		{
			pthread_mutex_unlock(&philo->meal_nb_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->meal_nb_mutex);
		philo = philo->next;
	}
}
