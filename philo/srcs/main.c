/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/03 15:52:33 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static int	free_memory(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->thread)
		free(data->thread);
	if (data->forks)
		free(data->forks);
	return (0);
}

static int	create_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nr_philos)
	{
		if (!data->to_eat)
		{
			if (pthread_create(&data->thread[i].tid, NULL,
					do_stuff, &data->thread[i]))
				return (1);
		}
		else
		{
			if (pthread_create(&data->thread[i].tid, NULL,
					do_stuff_count, &data->thread[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(data->thread[i].tid, NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (log_error("Incorrect amount or arguments provided\n"));
	if (init_data(&data, argv, argc))
		return (log_error("Malloc failure\n"));
	create_threads(&data);
	join_threads(&data);
	return (free_memory(&data));
}
