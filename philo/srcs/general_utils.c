/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/10 21:07:07 by nsterk        ########   odam.nl         */
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

unsigned long	timestamp(unsigned long start_ms)
{
	struct timeval	current;
	unsigned long	current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

void	naomi_sleep(t_thread *thread, unsigned long ms)
{
	t_data			*data;
	struct timeval	elapsed;
	unsigned long	elapsed_ms;

	data = (t_data *)thread->data;
	gettimeofday(&elapsed, NULL);
	elapsed_ms = (elapsed.tv_sec * 1000) + (elapsed.tv_usec / 1000);
	while (timestamp(elapsed_ms) < ms && someone_dead(data) == false)
		usleep(50);
}

void	usleep_adj(t_thread *thread, unsigned long start_ms)
{
	t_data	*data;

	data = (t_data *)thread->data;
	while (timestamp(start_ms) < thread->resume && !someone_dead(data))
		usleep(100);
}

int	free_memory(t_data *data)
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
