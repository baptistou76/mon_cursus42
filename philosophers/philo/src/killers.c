/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 08:13:21 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/20 07:56:09 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grim_reaper(t_philo *philo)
{
	t_philo	*tmp;
	t_data	*data;
	int		i;

	data = philo->data;
	i = 0;
	if (!philo || !data)
		return ;
	tmp = philo;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&tmp->meal_nb_mutex);
		pthread_mutex_destroy(&tmp->meal_eaten);
		pthread_mutex_destroy(&tmp->last_meal_mutex);
		tmp = tmp->next;
		i++;
	}
}

void	kill_them_all(t_data *data, t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*next;
	int		i;

	if (!data || !philo)
		return ;
	tmp = philo;
	grim_reaper(tmp);
	i = 0;
	while (i < data->nb_philos)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
		i++;
	}
	mutex_destroyer(data);
}

void	mutex_destroyer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
}

void	join_the_threads(t_philo *philo)
{
	t_data	*data;
	int		i;

	data = philo->data;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
		i++;
	}
}
