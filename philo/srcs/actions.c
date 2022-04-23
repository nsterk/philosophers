/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 20:47:14 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	do_eat(t_thread *thread, t_data *data)
{
	unsigned long	time_of_meal;

	pthread_mutex_lock(thread->left_fork);
	log_message(thread, FORK);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, FORK);
	time_of_meal = log_message(thread, EATING);
	thread->resume = time_of_meal + data->time_to_eat;
	thread->tod = time_of_meal + data->time_to_die;
	do_wait(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
}

void	do_sleep(t_thread *thread, t_data *data)
{
	if ((get_timestamp(data->start) + data->time_to_sleep) >= thread->tod)
		return ;
	thread->resume = log_message(thread, SLEEPING) + data->time_to_sleep;
	do_wait(thread, data->start);
}

void	do_think(t_thread *thread, t_data *data)
{
	if (get_timestamp(data->start) >= thread->tod)
		return ;
	thread->resume = log_message(thread, THINKING) + 1;
	do_wait(thread, data->start);
}

void	*do_die(t_thread *thread, t_data *data)
{
	thread->resume = thread->tod;
	do_wait(thread, data->start);
	if (!data->death)
		log_message(thread, DEAD);
	return (NULL);
}

void	do_wait(t_thread *thread, long long start_ms)
{
	while (get_timestamp(start_ms) < thread->resume)
		usleep(50);
	thread->state = FREE;
}
