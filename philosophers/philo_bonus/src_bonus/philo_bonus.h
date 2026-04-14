/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:06:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/05/14 21:55:00 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philos;
	int				meals_required;
	pthread_mutex_t	death_mutex;
	bool			is_dead;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	sem_t			*forks;
	sem_t			*meals_done;
	sem_t			*write_lock;
	sem_t			*death_lock;
	sem_t			*death_flag;
}					t_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	int				meal_nb;
	long long		last_meal;
	int				meals_eaten;
	pthread_mutex_t	meals_needed;
	pthread_mutex_t	last_meal_mutex;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_data			*data;
}					t_philo;

t_philo				*create_philo(int id, t_data *data);
t_philo				*add_philo(int i, t_data *data, t_philo *prev);
void				free_philos(t_philo *philo);
int					init_semaphore(t_data *data);
t_philo				*init_philos(t_data *data);
int					init_data(t_data *data, char **argv);
void				start_processes(t_philo *philo);
void				*routine(t_philo *philo);
long long			got_the_time(void);
long long			time_diff(long long past, long long pres);
void				time_sleep(long long time, t_philo *philo);
void				print_status(t_philo *philo, char *status);
int					ft_str_is_digit(const char *str);
long				ft_atol(const char *str);
void				cleanup_semaphores(t_data *data);
void				kill_them_all(t_philo *start, t_data *data);
void				*death_monitoring(void *arg);
void				wait_all(t_philo *philo);
void				philo_exiter(t_philo *philo, int status);
void				philo_take_forks(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleeping(t_philo *philo);
void				philo_released_forks(t_philo *philo);
void				philo_reaper(t_philo *philo);
void				*death_notifier(void *arg);

#endif
