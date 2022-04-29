/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log_messages.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 18:30:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/29 19:12:17 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	log_fork(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	thread->timestamp = get_timestamp(data->start);
	if ((thread->timestamp < thread->tod) && someone_dead(data) == 0)
		printf("%lu %i has taken a fork\n", thread->timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
}

void	log_eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	thread->timestamp = get_timestamp(data->start);
	if (thread->timestamp < thread->tod && someone_dead(data) == 0)
	{
		printf("%lu %i has taken a fork\n", thread->timestamp, thread->id);
		printf("%lu %i is eating\n", thread->timestamp, thread->id);
	}
	pthread_mutex_unlock(&data->write_mutex);
}

int		log_sleep(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	thread->timestamp = get_timestamp(data->start);
	if ((thread->timestamp + data->time_to_sleep
			< thread->tod) && someone_dead(data) == 0)
		printf("%lu %i is sleeping\n", thread->timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
	thread->resume = thread->timestamp + data->time_to_sleep;
	if (someone_dead(data))
		return (1);
	do_wait(thread, data->start);
	return (0);
}

void	log_think(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(&data->write_mutex);
	thread->timestamp = get_timestamp(data->start);
	if ((thread->timestamp < thread->tod) && someone_dead(data) == 0)
		printf("%lu %i is thinking\n", thread->timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
}
