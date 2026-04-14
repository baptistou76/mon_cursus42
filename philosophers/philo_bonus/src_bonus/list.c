/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:30:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/13 13:36:29 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*create_philo(int id, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->last_meal = 0;
	philo->meals_eaten = 0;
	philo->pid = -1;
	philo->data = data;
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

t_philo	*add_philo(int i, t_data *data, t_philo *prev)
{
	t_philo	*new;

	new = create_philo(i, data);
	if (!new)
		return (printf("Error: Philo allocation failed\n"), NULL);
	new->prev = prev;
	if (prev)
		prev->next = new;
	return (new);
}
