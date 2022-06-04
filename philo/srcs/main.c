/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/03 00:33:57 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
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

static int	validate_args(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
			return (1);
		i++;
	}
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
	return (0);
}

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
	if (validate_args(&data, argv, argc))
		return (log_error(&data, "Invalid arguments", 0));
	if (init_data(&data))
		return (log_error(&data, "Error initialising data", 0));
	if (create_threads(&data))
		return (log_error(&data, "Error creating threads", 1));
	if (join_threads(&data, 0))
		return (log_error(&data, "Error joining threads", 2));
	return (free_memory(&data));
}
