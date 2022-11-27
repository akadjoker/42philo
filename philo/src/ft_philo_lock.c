/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 17:35:25 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_is_locked(t_fork *fork, int value)
{
	pthread_mutex_lock(&fork->is_locked_mutex);
	fork->is_locked = value;
	pthread_mutex_unlock(&fork->is_locked_mutex);
}

int	is_locked(t_fork *fork)
{
	int	is_locked;

	pthread_mutex_lock(&fork->is_locked_mutex);
	is_locked = fork->is_locked;
	pthread_mutex_unlock(&fork->is_locked_mutex);
	return (is_locked);
}

void	set_someone_died(t_data *data, int value)
{
	pthread_mutex_lock(&data->no_one_died_mutex);
	data->no_one_died = !value;
	pthread_mutex_unlock(&data->no_one_died_mutex);
}

int	check_someone_died(t_data *data)
{
	int	someone_died;

	pthread_mutex_lock(&data->no_one_died_mutex);
	someone_died = !data->no_one_died;
	pthread_mutex_unlock(&data->no_one_died_mutex);
	return (someone_died);
}
