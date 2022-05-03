/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/03 15:48:55 by nsterk        ########   odam.nl         */
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
		i++;
	}
	return (0);
}

static int	init_forks(t_data *data, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		if (!i)
			data->thread[i].left_fork = &data->forks[amount - 1];
		else
			data->thread[i].left_fork = &data->forks[i - 1];
		data->thread[i].right_fork = &data->forks[i];
		i++;
	}
	return (0);
}

static int	init_states(t_data *data, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_mutex_init(&data->states[i], NULL))
			return (1);
		data->thread[i].state = &data->states[i];
		if (!i)
			data->thread[i].left_neighbour = &data->states[amount - 1];
		else
			data->thread[i].left_neighbour = &data->states[i - 1];
		if (i == (amount - 1))
			data->thread[i].right_neighbour = &data->states[0];
		else
			data->thread[i].right_neighbour = &data->states[i + 1];
		i++;
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (init_forks(data, data->nr_philos) || init_states(data, data->nr_philos))
		return (1);
	if (pthread_mutex_init(&data->write_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
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
	data->states = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->thread || !data->forks || !data->states)
		return (1);
	data->start = timestamp(0);
	init_threads(data);
	init_mutexes(data);
	return (0);
}
