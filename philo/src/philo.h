/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 18:58:12 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <pthread.h>

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define PURPLE "\033[1;35m"
# define BLUE "\033[1;36m"
# define YELLOW "\033[0;33m"
# define GREY "\033[0;40m"
# define PURPLE "\033[1;35m"
# define UNSET "\033[0m"

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

struct s_fork {
	int				is_locked;
	pthread_mutex_t	is_locked_mutex;
	pthread_mutex_t	mutex;
};

struct s_data {
	int				num_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	max_meals;
	int				real_meals;
	unsigned int	count_meals;
	t_fork			*forks;
	t_philo			*phillosophers;
	struct timeval	started_at;
	int				no_one_died;
	pthread_mutex_t	no_one_died_mutex;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	print_death_lock;
};

struct s_philo {
	int				id;
	int				display_id;
	unsigned int	dinners_had;
	struct timeval	last_meal;
	t_data			*data;
};

void			run_simulation(t_data *data);

void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			handle_death(t_philo *philo);

int				pretend_sleep(t_philo *philo, long amount);

int				is_int(char *number);
int				ft_atoi(const char *str);

unsigned long	get_elapsed_time(struct timeval since);

void			set_is_locked(t_fork *fork, int value);
int				is_locked(t_fork *fork);
void			set_someone_died(t_data *data, int value);
int				check_someone_died(t_data *data);

void			philo_show(t_philo *philo, char *message);

#endif /* !PHILO_H */
