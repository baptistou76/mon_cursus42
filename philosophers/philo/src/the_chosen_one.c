/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_chosen_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:01:39 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/20 09:17:53 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	the_chosen_one(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, the_one, (void *)philo) != 0)
	{
		join_the_threads(philo);
		return (printf("Error: Thread failed\n"), 1);
	}
	return (0);
}

void	*the_one(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(philo->right_fork);
	print_philo(philo, "has taken his right fork\n");
	usleep(philo->data->time_to_die * 1000);
	print_philo(philo, "died\n");
	set_philo_dead(philo->data, 1);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}
