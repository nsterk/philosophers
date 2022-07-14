/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/14 18:36:22 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int	log_error(t_data *data, enum e_error err)
{
	static const char	*msgs[] = {
		"Incorrect nr of arguments provided",
		"Invalid arguments provided",
		"Error initialising data"
		"Error creating threads",
		"Error joining threads"
	};

	if (err > E_INIT)
		free_memory(data);
	printf("%s\n", msgs[err]);
	return (1);
}

int	free_memory(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->diet_mutex);
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
	pthread_mutex_destroy(&data->write_mutex);
	return (0);
}
