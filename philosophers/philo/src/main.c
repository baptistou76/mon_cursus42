/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:27:17 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/20 07:56:16 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (args_to_data(&data, argv) == 1)
		return (printf("Error: Data initialization failed\n"), 1);
	philo = init_philos(&data);
	if (!philo)
		return (printf("Error: Philo initialization failed\n"), 1);
	forks_for_philos(&data, philo);
	if (!philo)
		return (printf("Error: Philo forks failed\n"), 1);
	if (lets_get_it_started(philo) != 0)
		return (printf("Error: Thread creation failed\n"), 1);
	join_the_threads(philo);
	kill_them_all(&data, philo);
	return (0);
}
