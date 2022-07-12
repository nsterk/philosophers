/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/12 17:27:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		data->thread[i].id = i + 1;
		data->thread[i].tod = data->time_to_die;
		data->thread[i].data = (t_data *)data;
		data->thread[i].to_eat = data->to_eat;
		data->thread[i].timestamp = 0;
		data->thread[i].last_meal = 0;
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->death = 0;
	data->thread = malloc(sizeof(t_thread) * data->nr_philos);
	if (!data->thread)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->forks)
	{
		free(data->thread);
		return (1);
	}
	data->start = timestamp(0) + (unsigned long)data->nr_philos + 2;
	init_threads(data);
	if (init_mutexes(data))
		return (1);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		if (!i)
			data->thread[i].left_fork = &data->forks[data->nr_philos - 1];
		else
			data->thread[i].left_fork = &data->forks[i - 1];
		data->thread[i].right_fork = &data->forks[i];
		if (pthread_mutex_init(&data->thread[i].eat, NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	return (0);
}
