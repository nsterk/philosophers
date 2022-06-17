/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/17 19:51:56 by nsterk        ########   odam.nl         */
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
	data->portion_control = false;
	data->to_eat = 0;
	if (argc == 6)
	{
		data->to_eat = ft_atoi(argv[5]);
		data->portion_control = true;
	}
	if (data->nr_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->to_eat < 0)
		return (1);
	return (0);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitoring_thread, NULL, monitor, data))
		return (1);
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->thread[i].tid, NULL,
				do_stuff, &data->thread[i]))
			return (1);
		// if (pthread_detach(data->thread[i].tid))
		// 	return (1);
		i++;
	}
	return (0);
}

static int	join_threads(t_data *data, int i)
{
	while (i < data->nr_philos)
		if (pthread_join(data->thread[i++].tid, NULL))
			return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (log_error(&data, E_AMOUNT));
	if (validate_args(&data, argv, argc))
		return (log_error(&data, E_INVALID));
	if (init_data(&data))
		return (log_error(&data, E_INIT)); //destroy mutexes moet evt nog hirna egbeuern
	if (create_threads(&data))
		return (log_error(&data, E_THREAD_CREAT));
	if (join_threads(&data, 0))
		return (log_error(&data, E_THREAD_JOIN));
	return (free_memory(&data));
}
