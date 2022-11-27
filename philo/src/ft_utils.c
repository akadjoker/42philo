/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:22:14 by lrosa-do          #+#    #+#             */
/*   Updated: 2022/11/27 17:57:56 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	i = 0;
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (str[i] == '-' && ++i)
		sign = -1;
	else if (str[i] == '+')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - '0');
	}
	return (result * sign);
}

void	philo_show(t_philo *philo, char *message)
{
	long			milis;
	pthread_mutex_t	*lock;

	lock = &philo->data->print_lock;
	pthread_mutex_lock(lock);
	if (!check_someone_died(philo->data))
	{
		milis = get_elapsed_time(philo->data->started_at);
		printf("%ld %d %s\n", milis, philo->display_id, message);
	}
	pthread_mutex_unlock(lock);
}

static int	will_overflow(int number, int digit)
{
	if (number > 0)
		return (number * 10 + digit < number);
	else
		return (number * 10 - digit > number);
}

int	is_int(char *number)
{
	int		i;
	int		is_negative;
	int		digit;
	long	as_int;

	i = 0;
	as_int = 0;
	is_negative = number[i] == '-';
	if (is_negative)
		i++;
	while (number[i])
	{
		digit = number[i] - '0';
		if (digit < 0 || digit > 9)
			return (0);
		if (will_overflow(as_int, digit))
			return (0);
		if (is_negative)
			as_int = as_int * 10 - digit;
		else
			as_int = as_int * 10 + digit;
		i++;
	}
	return (1);
}
