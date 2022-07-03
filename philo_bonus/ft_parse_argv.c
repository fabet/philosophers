/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabet <fabet@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:38:23 by fabet             #+#    #+#             */
/*   Updated: 2022/07/03 16:17:36 by fabet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_check_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_print_error("Error! Invalid number of arguments!\n");
		return (ERROR);
	}
	return (OK);
}

static t_sim_data	*ft_init_sim_data(int argc, char *argv[])
{
	t_sim_data	*sim_data;

	sim_data = (t_sim_data *)malloc(sizeof(t_sim_data));
	if (sim_data == NULL)
	{
		ft_print_error("Error! Failed to allocate memory!\n");
		return (NULL);
	}
	sim_data->number_of_philos = ft_strict_atoi(argv[1]);
	sim_data->time_to_die = ft_strict_atoi(argv[2]);
	sim_data->time_to_eat = ft_strict_atoi(argv[3]);
	sim_data->time_to_sleep = ft_strict_atoi(argv[4]);
	if (argc == 6)
		sim_data->number_of_meals = ft_strict_atoi(argv[5]);
	else
		sim_data->number_of_meals = 0;
	sim_data->is_stopped = FALSE;
	sem_unlink(OUTPUT_SEM);
	sim_data->output = sem_open(OUTPUT_SEM, O_CREAT, 0660, 1);
	sem_unlink(FORKS_SEM);
	sim_data->output = sem_open(FORKS_SEM, O_CREAT, 0660, sim_data->number_of_philos);
	return (sim_data);
}

static int	ft_check_sim_data(t_sim_data *sim_data)
{
	if (sim_data == NULL)
		return (ERROR);
	if (sim_data->number_of_philos == WRONG_FORMAT
		|| sim_data->time_to_die == WRONG_FORMAT
		|| sim_data->time_to_eat == WRONG_FORMAT
		|| sim_data->time_to_sleep == WRONG_FORMAT
		|| sim_data->number_of_meals == WRONG_FORMAT)
	{
		free(sim_data);
		ft_print_error("Error! Invalid arguments format!\n");
		return (ERROR);
	}
	return (OK);
}

t_sim_data	*ft_parse_argv(int argc, char *argv[])
{
	t_sim_data	*sim_data;

	if (ft_check_argc(argc) == ERROR)
		return (NULL);
	sim_data = ft_init_sim_data(argc, argv);
	if (ft_check_sim_data(sim_data) == ERROR)
		return (NULL);
	gettimeofday(&sim_data->start_time, NULL);
	return (sim_data);
}