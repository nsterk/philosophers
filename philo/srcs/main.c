/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/26 20:44:13 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static void	free_memory(t_data *data)
{
	int	i;

	free(data->forks);
	free(data->thread);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return ;
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
	spawn_threads(&data);
	free_memory(&data);
	return (0);
}
