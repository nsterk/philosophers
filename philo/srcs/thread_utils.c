/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/15 13:36:08 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

void	log_message(t_thread *thread, enum e_msg msg)
{
	t_data				*data;
	static const char	*msgs[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	data = (t_data *)thread->data;
	pthread_mutex_lock(&data->write_mutex);
	thread->timestamp = timestamp(data->start);
	if (someone_dead(data) == false && philos_full(data) == false)
		printf("%lu %d %s\n", thread->timestamp, thread->id, msgs[msg]);
	if (msg == E_DIE)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death = true;
		pthread_mutex_unlock(&data->death_mutex);
	}
	pthread_mutex_unlock(&data->write_mutex);
}

bool	someone_dead(t_data *data)
{
	bool	death;

	death = false;
	pthread_mutex_lock(&data->death_mutex);
	if (data->death)
		death = true;
	pthread_mutex_unlock(&data->death_mutex);
	return (death);
}

bool	philos_full(t_data *data)
{
	bool	filled;

	if (data->diet == false)
		return (false);
	filled = false;
	pthread_mutex_lock(&data->diet_mutex);
	if (data->full_philos == data->nr_philos)
		filled = true;
	pthread_mutex_unlock(&data->diet_mutex);
	return (filled);
}

bool	time_to_die(t_data *data, t_thread *thread)
{
	bool	time_to_die;

	time_to_die = false;
	pthread_mutex_lock(&thread->eat);
	if (timestamp(data->start) > (thread->last_meal + data->time_to_die))
		time_to_die = true;
	pthread_mutex_unlock(&thread->eat);
	return (time_to_die);
}
