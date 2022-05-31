/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/31 18:06:01 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static int	create_threads(t_data *data)
{
	int	i;

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

static int	join_threads(t_data *data, int i)
{
	while (i < data->nr_philos)
	{
		if (pthread_join(data->thread[i].tid, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (log_error(&data, "Incorrect amount of arguments provided", 0));
	if (init_data(&data, argv, argc))
		return (log_error(&data, "Error initialising data", 0));
	if (create_threads(&data))
		return (log_error(&data, "Error creating threads", 1));
	if (join_threads(&data, 0))
		return (log_error(&data, "Error joining threads", 2));
	return (free_memory(&data));
}
