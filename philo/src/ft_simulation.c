/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 18:30:00 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*create_philo_thread(void *data)
{
	t_philo	*philo;

	philo = data;
	while (!check_someone_died(philo->data))
	{
		philo_eat(data);
		if (philo->dinners_had >= philo->data->max_meals)
			break ;
		philo_sleep(data);
		philo_think(data);
	}
	return (data);
}

void	init_philo(pthread_t *ids, t_data *data)
{
	int				i;
	t_philo			*philosophers;
	t_philo			*philo;

	i = 0;
	philosophers = malloc(sizeof(t_philo) * data->num_philosophers);
	memset(philosophers, 0, sizeof(t_philo) * data->num_philosophers);
	data->phillosophers = philosophers;
	while (i < data->num_philosophers)
	{
		philo = &philosophers[i];
		philo->id = i;
		philo->display_id = i + 1;
		philo->data = data;
		philo->last_meal = data->started_at;
		philo->dinners_had = 0;
		pthread_create(&ids[i], NULL, create_philo_thread, philo);
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->num_philosophers);
	if (data->forks == NULL)
		return ;
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		pthread_mutex_init(&data->forks[i].is_locked_mutex, NULL);
		data->forks[i].is_locked = 0;
		i++;
	}
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->count_meals += data->phillosophers[i].dinners_had;
		pthread_mutex_destroy(&data->forks[i].mutex);
		pthread_mutex_destroy(&data->forks[i].is_locked_mutex);
		i++;
	}
	free(data->forks);
}

void	run_simulation(t_data *data)
{
	pthread_t	*philosopher_ids;
	int			i;

	philosopher_ids = malloc(sizeof(pthread_t) * data->num_philosophers);
	if (philosopher_ids == NULL)
		return ;
	init_forks(data);
	init_philo(philosopher_ids, data);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(philosopher_ids[i], NULL);
		i++;
	}
	destroy_forks(data);
	free(philosopher_ids);
	free(data->phillosophers);
}
