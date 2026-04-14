/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:53:17 by bcaumont          #+#    #+#             */
/*   Updated: 2025/03/26 15:19:51 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				meals_required;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	long long		start_time;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				meal_nb;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meal_eaten;
	pthread_mutex_t	meal_nb_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_data			*data;
}					t_philo;

/* Here we go */
int					lets_get_it_started(t_philo *philo);
int					the_chosen_one(t_philo *philo);
int					shadow_of_death(t_philo *philo);

/* Death is commin' */
void				*are_you_dead_yet(void *arg);
void				set_philo_dead(t_data *data, int doa);
int					is_philo_dead(t_data *data);
void				deadly_mutex(void *arg);
void				hungry_mutex(void *arg);

/* Routine */
void				*routine(void *arg);
void				enjoy_your_meal(t_philo *philo);
void				taking_forks(t_philo *philo);
void				released_forks(t_philo *philo);
void				*the_one(void *arg);
void				eating_time(t_philo *philo);

/* Philos*/
t_philo				*init_philos(t_data *data);
t_philo				*add_philo(int i, t_data *data, t_philo *prev);
t_philo				*create_philos(int id, t_data *data);
t_philo				*forks_for_philos(t_data *data, t_philo *philo);

/* Data */
int					args_to_data(t_data *data, char **argv);
int					forks_and_threads(t_data *data);

/* Utils */
void				print_philo(t_philo *philo, char *str);
long				ft_atol(const char *str);
int					ft_str_is_digit(const char *str);

/* Time is on my side, yes it is */
long long			got_the_time(void);
long long			time_diff(long long past, long long pres);
void				time_sleep(long long time, t_philo *philo);

/* Killers */
void				kill_them_all(t_data *data, t_philo *philo);
void				grim_reaper(t_philo *philo);
void				mutex_destroyer(t_data *data);
void				join_the_threads(t_philo *philo);

#endif