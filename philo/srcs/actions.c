/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 20:16:08 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	do_eating(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	log_message(thread, FORK);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, FORK);
	thread->last_meal = log_message(thread, EATING);
	thread->resume = thread->last_meal + data->time_to_eat;
	thread->tod = thread->last_meal + data->time_to_die;
	be_busy(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
}

void	do_sleeping(t_thread *thread, t_data *data)
{
	if ((get_timestamp(data->start) + data->time_to_sleep) >= thread->tod)
		return ;
	thread->resume = log_message(thread, SLEEPING) + data->time_to_sleep;
	be_busy(thread, data->start);
}

void	do_thinking(t_thread *thread, t_data *data)
{
	if (get_timestamp(data->start) >= thread->tod)
		return ;
	thread->resume = log_message(thread, THINKING) + 1;
	be_busy(thread, data->start);
}

void	*do_dying(t_thread *thread, t_data *data)
{
	thread->resume = thread->tod;
	be_busy(thread, data->start);
	log_message(thread, DEAD);
	return (NULL);
}

void	*do_new_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (!thread->id % 2)
		usleep(100);
	thread->tod = get_timestamp(data->start) + data->time_to_die;
	while (1)
	{
		if (data->death)
			return (NULL);
		if (get_timestamp(data->start) >= thread->tod)
			return (do_dying(thread, data));
		do_eating(thread, data);
		do_sleeping(thread, data);
		do_thinking(thread, data);
	}
	return (NULL);
}
