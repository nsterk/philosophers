/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/30 16:14:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		// if (pthread_mutex_init(&data->status_m[i], NULL))
		// 	return (1);
		if (!i)
		{
			data->thread[i].left_fork = &data->forks[data->nr_philos - 1];
		}
		else
			data->thread[i].left_fork = &data->forks[data->thread[i].id - 2];
		data->thread[i].right_fork = &data->forks[data->thread[i].id - 1];
		i++;
	}
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	return (0);
}

static int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		data->thread[i].id = i + 1;
		// data->thread[i].last_meal = 0;
		data->thread[i].tod = data->time_to_die;
		data->thread[i].data = (t_data *)data;
		data->thread[i].times_eaten = 0;
		data->thread[i].timestamp = 0;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv, int argc)
{
	data->nr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->to_eat = ft_atoi(argv[5]);
	else
		data->to_eat = 0;
	if (data->nr_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->to_eat < 0)
		return (1);
	data->death = 0;
	data->thread = malloc(sizeof(t_thread) * data->nr_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->thread || !data->forks)
		return (1);
	data->start = get_timestamp(0);
	init_threads(data);
	init_mutexes(data);
	return (0);
}
