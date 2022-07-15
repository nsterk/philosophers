/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/15 13:31:27 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

static void	mark_full(t_data *data)
{
	pthread_mutex_lock(&data->diet_mutex);
	data->full_philos++;
	pthread_mutex_unlock(&data->diet_mutex);
}

static void	take_forks(t_thread *thread)
{
	pthread_mutex_lock(thread->left_fork);
	log_message(thread, E_FORK);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, E_FORK);
	return ;
}

void	*do_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (data->nr_philos == 1)
		return (one_philosopher(thread, data));
	while (timestamp(0) < data->start)
		usleep(100);
	if (!(thread->id % 2))
		usleep(500);
	while (someone_dead(data) == false && philos_full(data) == false)
	{
		take_forks(thread);
		do_eat(thread, data);
		do_sleep(thread, data);
		log_message(thread, E_THINK);
	}
	return (NULL);
}

void	do_eat(t_thread *thread, t_data *data)
{
	log_message(thread, E_EAT);
	thread->to_eat--;
	if (data->diet == true && thread->to_eat == 0)
		mark_full(data);
	pthread_mutex_lock(&thread->eat);
	thread->last_meal = thread->timestamp;
	pthread_mutex_unlock(&thread->eat);
	usleep_adj(data->time_to_eat);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
}

void	do_sleep(t_thread *thread, t_data *data)
{
	log_message(thread, E_SLEEP);
	thread->resume = thread->timestamp + data->time_to_sleep;
	usleep_adj(data->time_to_sleep);
}
