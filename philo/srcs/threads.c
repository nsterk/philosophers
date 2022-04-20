/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 20:09:56 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*do_stuff(void *arg)
{
	t_thread	*thread;	
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (!thread->id % 2)
		usleep(100);
	while (1)
	{
		if ((get_timestamp(data->start_ms) - thread->last_meal) <= data->time_to_die)
		{
			eat(thread, data);
			log_message(thread, get_timestamp(data->start_ms), STATE_SLEEP);
			usleep(data->time_to_sleep * 1000);
		}
		else
		{
			log_message(thread, get_timestamp(data->start_ms), STATE_DEAD);
			break ;
		}
	}
	return (NULL);
}

void	eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	pthread_mutex_lock(thread->right_fork);
	thread->last_meal = get_timestamp(data->start_ms);
	log_message(thread, thread->last_meal, STATE_EAT);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
	return ;
}

int	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->thread[i].tid, NULL,
				do_stuff, &data->thread[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(data->thread[i].tid, NULL);
		i++;
	}
	return (0);
}
