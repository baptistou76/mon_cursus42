/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:02:03 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/27 17:05:38 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (init_data(&data, argv) == 1)
		return (printf("Error: data initialization failed\n"), 1);
	philo = init_philos(&data);
	if (!philo)
		return (printf("Error: philo initialization failed\n"), 1);
	start_processes(philo);
	cleanup_semaphores(&data);
	free_philos(philo);
	return (0);
}
