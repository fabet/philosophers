/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabet <fabet@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 12:15:49 by fabet             #+#    #+#             */
/*   Updated: 2022/07/01 20:54:41 by fabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strict_atoi(const char *str)
{
	int	result;
	int	counter;

	result = 0;
	counter = 0;
	while (*str)
	{
		if (*str >= 48 && *str <= 57 && counter < 20)
		{
			result = (*str - '0') + result * 10;
			str++;
			counter++;
		}
		else
			return (-1);
	}
	return (result);
}

long	ft_count_timestamp_in_ms(
			struct timeval start_time,
			struct timeval actual_time)
{
	long	seconds;
	long	useconds;

	seconds = actual_time.tv_sec - start_time.tv_sec;
	useconds = actual_time.tv_usec - start_time.tv_usec;
	return (seconds * 1000 + useconds / 1000.0);
}

void	ft_sleep(int ms)
{
	struct timeval	start_time;
	struct timeval	actual_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&actual_time, NULL);
	while (ft_count_timestamp_in_ms(start_time, actual_time) < ms)
	{
		gettimeofday(&actual_time, NULL);
		usleep(10);
	}
}

int	ft_is_stopped(t_sim_data *sim_data)
{
	int	is_stopped;

	pthread_mutex_lock(&sim_data->sim_mutex);
	is_stopped = sim_data->is_stopped;
	pthread_mutex_unlock(&sim_data->sim_mutex);
	return (is_stopped);
}