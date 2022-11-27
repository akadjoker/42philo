/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 18:12:34 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	identify_forks(t_philo *philo, t_fork **right, t_fork **left)
{
	*right = &philo->data->forks[philo->id];
	if (philo->display_id == philo->data->num_philosophers)
		*left = &philo->data->forks[0];
	else
		*left = &philo->data->forks[philo->id + 1];
}

void	pickup_forks(t_philo *philo, t_fork *right, t_fork *left)
{
	t_fork	*first;
	t_fork	*second;

	if (philo->id % 2 == 0)
	{
		first = right;
		second = left;
	}
	else
	{
		first = left;
		second = right;
	}
	pthread_mutex_lock(&first->mutex);
	set_is_locked(first, 1);
	philo_show(philo, "\033[1;35mhas taken a fork\033[0m");
	while (is_locked(second))
		if (pretend_sleep(philo, 1) == 0)
			return (handle_death(philo));
	pthread_mutex_lock(&second->mutex);
	set_is_locked(second, 1);
	philo_show(philo, "\033[0;33mhas taken a fork\033[0m");
}

int	can_eat(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	if (right_fork == left_fork)
		return (0);
	if (get_elapsed_time(philo->last_meal) > philo->data->time_to_die / 2
		&& !is_locked(right_fork))
		return (1);
	if (is_locked(right_fork) || is_locked(left_fork))
		return (0);
	return (1);
}

void	handle_death(t_philo *philo)
{
	long	milis;

	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->print_death_lock);
	milis = get_elapsed_time(philo->data->started_at);
	if (!check_someone_died(philo->data))
		printf("%ld %d %s\n", milis, philo->display_id, "\033[1;31mdied\033[0m");
	set_someone_died(philo->data, 1);
	pthread_mutex_unlock(&philo->data->print_death_lock);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	philo_eat(t_philo *philo)
{
	t_fork	*right;
	t_fork	*left;

	if (get_elapsed_time(philo->last_meal) >= philo->data->time_to_die)
		return (handle_death(philo));
	if (check_someone_died(philo->data))
		return ;
	identify_forks(philo, &right, &left);
	while (!can_eat(philo, right, left))
	{
		if (get_elapsed_time(philo->last_meal) >= philo->data->time_to_die)
			return (handle_death(philo));
		usleep(100);
	}
	pickup_forks(philo, right, left);
	philo_show(philo, "\033[0;32mis eating\033[0m");
	gettimeofday(&philo->last_meal, NULL);
	if (pretend_sleep(philo, philo->data->time_to_eat) == 0)
		handle_death(philo);
	philo->dinners_had++;
	pthread_mutex_unlock(&right->mutex);
	set_is_locked(right, 0);
	pthread_mutex_unlock(&left->mutex);
	set_is_locked(left, 0);
}
