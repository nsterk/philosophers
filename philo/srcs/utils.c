/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 13:51:52 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	get_timestamp(long long start_ms)
{
	struct timeval	current;
	long long		current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

void	*check_fatalities(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->death_mutex);
	while (!data->death)
	{
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->death_mutex);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (NULL);
}

void	log_message(t_thread *thread, long timestamp, int state)
{
	t_data	*data;

	data = (t_data *)thread->data;
	thread->last_meal = timestamp;
	pthread_mutex_lock(&data->write_mutex);
	if (state == STATE_EAT)
		printf("%ld %i is eating\n", timestamp, thread->id);
	else if (state == STATE_DEAD)
		printf("%ld %i has died\n", timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
}
