/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:32:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/26 15:22:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_to_data(t_data *data, char **argv)
{
	if (!ft_str_is_digit(argv[1]) || !ft_str_is_digit(argv[2])
		|| !ft_str_is_digit(argv[3]) || !ft_str_is_digit(argv[4]) || (argv[5]
			&& !ft_str_is_digit(argv[5])))
		return (1);
	data->nb_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->meals_required = -1;
	data->is_dead = 0;
	if (argv[5])
		data->meals_required = ft_atol(argv[5]);
	if (data->nb_philos <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (argv[5] && data->meals_required <= 0))
		return (1);
	return (forks_and_threads(data));
}

int	forks_and_threads(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->start_time = got_the_time();
	return (0);
}
