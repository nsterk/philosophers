/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/03 00:11:07 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdlib.h>

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i);
}

static bool	valid_args(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
			return (false);
		i++;
	}
	data->nr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->philo.to_eat = ft_atoi(argv[5]);
	else
		data->philo.to_eat = 0;
	if (data->nr_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->philo.to_eat < 0)
		return (false);
	return (true);
}

int	init_data(t_data *data, char **argv, int argc)
{
	if (valid_args(data, argv, argc) == false)
		return (1);
	data->pid = malloc(sizeof(pid_t) * data->nr_philos);
	if (!data->pid)
		return (1);
	data->philo.id = 0;
	data->philo.resume = 0;
	data->start = timestamp(0);
	data->philo.timestamp = data->start;
	return (0);
}
