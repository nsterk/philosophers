/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 16:24:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static int	init_data(t_data *data, char **argv, int argc)
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
	data->thread = malloc(sizeof(t_thread) * data->nr_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nr_philos);
	if (!data->thread || !data->forks)
		return (1);
	data->start_ms = get_timestamp(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect nr of arguments provided\n");
		return (0);
	}
	if (init_data(&data, argv, argc))
	{
		printf("woopsie poopsie in init_data\n");
		return (0);
	}
	return (0);
}
