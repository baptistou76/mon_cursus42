/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:06:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/14 22:18:28 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_processes(t_philo *philo)
{
	t_philo	*start;
	int		i;
	t_data	*data;

	start = philo;
	data = philo->data;
	i = 0;
	while (i < data->nb_philos)
	{
		philo->pid = fork();
		if (philo->pid == 0)
		{
			philo->pid = getpid();
			routine(philo);
		}
		else if (philo->pid < 0)
		{
			printf("Error: fork failed\n");
			exit(1);
		}
		philo = philo->next;
		usleep(50);
		i++;
	}
	wait_all(start);
}

void	*routine(t_philo *philo)
{
	pthread_t	monitor;
	pthread_t	notifier;

	philo->last_meal = got_the_time();
	pthread_create(&monitor, NULL, &death_monitoring, philo);
	pthread_detach(monitor);
	pthread_create(&notifier, NULL, &death_notifier, philo);
	pthread_detach(notifier);
	while (1)
	{
		philo_take_forks(philo);
		philo_eat(philo);
		philo_reaper(philo);
		philo_sleeping(philo);
		philo_released_forks(philo);
	}
}

void	*death_monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(1000);
		sem_wait(philo->data->death_lock);
		if (time_diff(philo->last_meal,
				got_the_time()) > philo->data->time_to_die
			&& !philo->data->is_dead)
		{
			if (!philo->data->is_dead)
			{
				print_status(philo, "died");
				philo->data->is_dead = true;
				sem_post(philo->data->death_flag);
				sem_post(philo->data->death_lock);
				exit(1);
			}
			sem_post(philo->data->death_lock);
			exit(1);
		}
		sem_post(philo->data->death_lock);
	}
	return (NULL);
}

void	*death_notifier(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->death_flag);
	sem_wait(philo->data->death_lock);
	if (!philo->data->is_dead)
		philo->data->is_dead = true;
	sem_post(philo->data->death_lock);
	philo_exiter(philo, 0);
	return (NULL);
}
