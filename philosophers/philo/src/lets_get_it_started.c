/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_get_it_started.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:13:59 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/26 10:13:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lets_get_it_started(t_philo *philo)
{
	int	i;

	if (philo->data->nb_philos == 1)
		the_chosen_one(philo);
	else
	{
		i = 0;
		while (i < philo->data->nb_philos)
		{
			pthread_mutex_lock(&philo->last_meal_mutex);
			philo->last_meal = got_the_time();
			pthread_mutex_unlock(&philo->last_meal_mutex);
			if (pthread_create(&philo->thread, NULL, routine,
					(void *)philo) != 0)
			{
				join_the_threads(philo);
				return (printf("Error: Thread failed\n"), 1);
			}
			usleep(50);
			philo = philo->next;
			i++;
		}
		shadow_of_death(philo);
	}
	return (0);
}

int	shadow_of_death(t_philo *philo)
{
	pthread_t	reaper;

	if (pthread_create(&reaper, NULL, are_you_dead_yet, (void *)philo) != 0)
		return (printf("Error: Death monitoring failed\n"), 1);
	pthread_join(reaper, NULL);
	return (0);
}
