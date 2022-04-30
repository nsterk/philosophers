/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/30 16:42:12 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	log_message(thread, e_fork);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, e_fork);
	log_message(thread, e_eat);
	thread->resume = thread->timestamp + data->time_to_eat;
	thread->tod = thread->timestamp + data->time_to_die;
	do_wait(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
}

void	do_sleep(t_thread *thread, t_data *data)
{
	log_message(thread, e_sleep);
	thread->resume = thread->timestamp + data->time_to_sleep;
	do_wait(thread, data->start);
}

void	think(t_thread *thread, t_data *data)
{
	log_message(thread, e_think);
}

void	*die(t_thread *thread, t_data *data)
{
	thread->resume = thread->tod;
	do_wait(thread, data->start);
	log_message(thread, e_die);
	printf("tod: %lu	timestamp: %lu\n", thread->tod, thread->timestamp);
	return (NULL);
}

void	do_wait(t_thread *thread, long long start_ms)
{
	t_data	*data;

	data = (t_data *)thread->data;
	while (get_timestamp(start_ms) < thread->resume && !someone_dead(data))
		usleep(100);
}
