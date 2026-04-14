/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:32:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/14 22:04:11 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_exiter(t_philo *philo, int status)
{
	cleanup_semaphores(philo->data);
	free_philos(philo);
	exit(status);
}

void	free_philos(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*head;

	if (!philo)
		return ;
	head = philo;
	while (philo)
	{
		tmp = philo->next;
		free(philo);
		if (tmp == head)
			break ;
		philo = tmp;
	}
}

void	cleanup_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->write_lock);
	sem_close(data->death_lock);
	sem_close(data->death_flag);
	sem_close(data->meals_done);
	sem_unlink("/forks");
	sem_unlink("/meals_done");
	sem_unlink("/death_flag");
	sem_unlink("/write_lock");
	sem_unlink("/death_lock");
}

void	wait_all(t_philo *philo)
{
	int		i;
	t_philo	*start;

	start = philo;
	i = 0;
	while (i < start->data->nb_philos)
	{
		sem_wait(start->data->meals_done);
		start = start->next;
		i++;
	}
	i = 0;
	while (i < philo->data->nb_philos)
	{
		waitpid(philo->pid, NULL, 0);
		philo = philo->next;
		i++;
	}
}
