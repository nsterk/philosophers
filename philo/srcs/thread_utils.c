/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/17 20:32:12 by nsterk        ########   odam.nl         */
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
	// printf("\033[34mthread %d	last_meal: %lu	timestamp: %lu\033[0m\n", thread->id, thread->last_meal, thread->timestamp);
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

bool	time_to_die(t_data *data, t_thread *thread)
{
	bool	time_to_die;

	time_to_die = false;
	pthread_mutex_lock(&thread->eat);
	if (timestamp(data->start) >= (thread->last_meal + data->time_to_die))
		time_to_die = true;
	pthread_mutex_unlock(&thread->eat);
	return (time_to_die);
}

int	create_monitor(t_data *data, t_thread *thread)
{
	if (pthread_create(&thread->monitor, NULL, monitor_thread, thread))
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death = true;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (someone_dead(data) == false)
	{
		i = 0;
		while (i < data->nr_philos && someone_dead(data) == false)
		{
			pthread_mutex_lock(&data->thread[i].eat);
			if (timestamp(data->start) > (data->thread[i].last_meal + \
							data->time_to_die))
				log_message(&data->thread[i], E_DIE);
			pthread_mutex_unlock(&data->thread[i].eat);
			i++;
		}
	}
	return (NULL);
}
