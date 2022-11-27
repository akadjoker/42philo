/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 18:58:36 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_help(void)
{
	printf("\033[1;31m Error, please ...\n");
	printf("\033[1;35mAll the times are in milliseconds.\n"
		"All arguments must be positive integers\033[0m\n");
	return (0);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (print_help());
	i = 1;
	while (i < argc)
	{
		if (!is_int(argv[i]))
			return (print_help());
		if (ft_atoi(argv[i]) < 0)
			return (print_help());
		i++;
	}
	return (argc);
}

void	trace_eats(t_data	*data)
{
	if (data->real_meals == -1)
		return ;
	if (data->count_meals > 0)
	{
		printf("\033[1;35mWas serve %d  spagetti\n", data->count_meals);
		printf("Philo eat %d  times\033[0m\n", \
		(data->count_meals / data->num_philosophers));
	}
}

void	init_mutex(t_data	*data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->no_one_died_mutex, NULL);
	pthread_mutex_init(&data->print_death_lock, NULL);
	run_simulation(data);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->no_one_died_mutex);
	pthread_mutex_destroy(&data->print_death_lock);
	trace_eats(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_args(argc, argv) == 0)
		return (1);
	gettimeofday(&data.started_at, NULL);
	data.num_philosophers = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.no_one_died = 1;
	data.count_meals = 0;
	data.max_meals = -1;
	data.real_meals = -1;
	if (argc == 6)
	{
		data.max_meals = ft_atoi(argv[5]);
		data.real_meals = (int) data.max_meals;
	}
	init_mutex(&data);
}
