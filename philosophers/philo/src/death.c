/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:01:00 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 14:43:53 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_check_each(t_philo *philo)
{
	t_data	*data;
	int		i;
	int		finished_philos;

	i = 0;
	data = philo->data;
	finished_philos = 0;
	if (data->meals_required == -1)
		return ;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&philo->meal_nb_mutex);
		if (philo->meal_nb >= data->meals_required)
			finished_philos++;
		pthread_mutex_unlock(&philo->meal_nb_mutex);
		philo = philo->next;
		i++;
	}
	if (finished_philos == data->nb_philos)
		set_philo_dead(philo->data, 1);
}

int	is_philo_dead(t_data *data)
{
	int	doa;

	doa = 0;
	pthread_mutex_lock(&data->death_mutex);
	doa = data->is_dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (doa);
}

void	set_philo_dead(t_data *data, int doa)
{
	pthread_mutex_lock(&data->death_mutex);
	data->is_dead = doa;
	pthread_mutex_unlock(&data->death_mutex);
}

void	*are_you_dead_yet(void *arg)
{
	t_philo	*philo;
	t_philo	*current;
	t_data	*data;
	int		i;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!is_philo_dead(data))
	{
		i = -1;
		current = philo;
		while (++i < data->nb_philos && !(is_philo_dead(data)))
		{
			deadly_mutex(current);
			current = current->next;
		}
		if (is_philo_dead(data))
			break ;
		hungry_mutex(current);
		philo_check_each(current);
		usleep(5);
	}
	return (NULL);
}
