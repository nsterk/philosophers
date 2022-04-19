/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/19 18:23:00 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	get_timestamp(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*check_fatalities(void *arg)
{
	t_data	*data;

	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->death)
			return (NULL);
		pthread_mutex_unlock(&data->death_mutex);
	}
		printed = 1;
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
