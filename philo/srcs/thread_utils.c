/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/04 16:44:54 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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
	if (someone_dead(data) == false)
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
