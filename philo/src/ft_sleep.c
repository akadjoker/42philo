/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 17:57:47 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	philo_show(philo, "\033[1;36mis sleeping\033[0m");
	if (pretend_sleep(philo, philo->data->time_to_sleep) == 0)
		handle_death(philo);
}

void	philo_think(t_philo *philo)
{
	long	safe_time_to_think;

	philo_show(philo, "\033[0;40mis thinking\033[0m");
	safe_time_to_think = philo->data->time_to_die - philo->data->time_to_eat
		- philo->data->time_to_sleep;
	safe_time_to_think /= 2;
	if (safe_time_to_think < 0)
		return ;
	pretend_sleep(philo, safe_time_to_think);
}

int	pretend_sleep(t_philo *philo, long amount)
{
	long			current;
	long			last_meal;
	struct timeval	started_sleep;

	current = 0;
	gettimeofday(&started_sleep, NULL);
	while (current < amount)
	{
		usleep(100);
		last_meal = get_elapsed_time(philo->last_meal);
		if (last_meal >= philo->data->time_to_die)
			return (0);
		current = get_elapsed_time(started_sleep);
	}
	return (1);
}
