/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/26 20:45:28 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	do_eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	log_fork(thread, data);
	// log_message(thread, FORK1);
	pthread_mutex_lock(thread->right_fork);
	log_eat(thread, data);
	// thread->last_meal = thread->timestamp;
	// thread->last_meal = log_message(thread, FORK2);
	// time_of_meal = log_message(thread, EATING);
	thread->resume = thread->timestamp + data->time_to_eat;
	thread->tod = thread->timestamp + data->time_to_die;
	do_wait(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
}

void	do_sleep(t_thread *thread, t_data *data)
{
	// if ((get_timestamp(data->start) + data->time_to_sleep) >= thread->tod)
	// 	return ;
	// thread->resume = log_message(thread, SLEEPING) + data->time_to_sleep;
	log_sleep(thread, data);
	thread->resume = thread->timestamp + data->time_to_sleep;
	do_wait(thread, data->start);
}

void	do_think(t_thread *thread, t_data *data)
{
	if (get_timestamp(data->start) > thread->tod)
		return ;
	log_message(thread, THINKING);
	// do_wait(thread, data->start);
}

void	*do_die(t_thread *thread, t_data *data)
{
	thread->resume = thread->tod;
	do_wait(thread, data->start);
	pthread_mutex_lock(&data->death_mutex);
	if (data->death)
	{
		pthread_mutex_unlock(&data->death_mutex);
		return (NULL);
	}
	data->death = 1;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->write_mutex);
	printf("%lu %i died\n", get_timestamp(data->start), thread->id);
	pthread_mutex_unlock(&data->write_mutex);
	return (NULL);
}

void	do_wait(t_thread *thread, long long start_ms)
{
	while (get_timestamp(start_ms) < thread->resume)
		usleep(100);
}
