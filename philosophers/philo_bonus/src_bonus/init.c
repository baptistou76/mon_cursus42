/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:44:21 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/14 22:16:26 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	if (!ft_str_is_digit(argv[1]) || !ft_str_is_digit(argv[2])
		|| !ft_str_is_digit(argv[3]) || !ft_str_is_digit(argv[4]) || (argv[5]
			&& !ft_str_is_digit(argv[5])))
		return (1);
	data->nb_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->meals_required = -1;
	data->is_dead = false;
	if (argv[5])
		data->meals_required = ft_atol(argv[5]);
	if (data->nb_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (argv[5] && data->meals_required <= 0))
		return (1);
	init_semaphore(data);
	data->start_time = got_the_time();
	return (0);
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

int	init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/death_lock");
	sem_unlink("/death_flag");
	sem_unlink("/meals_done");
	data->meals_done = sem_open("/meals_done", O_CREAT, 0644, 0);
	if (data->meals_done == SEM_FAILED)
		return (printf("Error: sem_open(eat)failed"), 1);
	data->death_flag = sem_open("/death_flag", O_CREAT, 0644, 0);
	if (data->death_flag == SEM_FAILED)
		return (printf("Error: sem_open(death_flag)failed"), 1);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->nb_philos);
	if (data->forks == SEM_FAILED)
		return (printf("Error: sem_open(forks)failed\n"), 1);
	data->write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	if (data->write_lock == SEM_FAILED)
		return (printf("Error: sem_open(write)failed\n"), 1);
	data->death_lock = sem_open("/death_lock", O_CREAT, 0644, 1);
	if (data->death_lock == SEM_FAILED)
		return (printf("Error: sem_open(death)failed\n"), 1);
	return (0);
}
