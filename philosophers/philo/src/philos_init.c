/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:57:13 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/20 07:56:28 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philos(int id, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->data = data;
	philo->last_meal = 0;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->meal_nb = 0;
	philo->thread = 0;
	philo->next = NULL;
	philo->prev = NULL;
	pthread_mutex_init(&philo->meal_eaten, NULL);
	pthread_mutex_init(&philo->meal_nb_mutex, NULL);
	pthread_mutex_init(&philo->last_meal_mutex, NULL);
	return (philo);
}

t_philo	*add_philo(int i, t_data *data, t_philo *prev)
{
	t_philo	*new;

	new = create_philos(i, data);
	if (!new)
		return (printf("Error: Philo allocation failed\n"), NULL);
	new->prev = prev;
	if (prev)
		prev->next = new;
	return (new);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*head;
	t_philo	*prev;
	int		i;

	i = 1;
	head = NULL;
	prev = NULL;
	while (i <= data->nb_philos)
	{
		prev = add_philo(i, data, prev);
		if (!prev)
			return (NULL);
		if (!head)
			head = prev;
		i++;
	}
	if (head && prev)
	{
		head->prev = prev;
		prev->next = head;
	}
	return (head);
}

t_philo	*forks_for_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philo->right_fork = &data->forks[i];
		philo->left_fork = &data->forks[(i + 1) % data->nb_philos];
		philo = philo->next;
		i++;
	}
	return (philo);
}
