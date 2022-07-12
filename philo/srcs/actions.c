/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/12 17:39:04 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

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
	while (someone_dead(data) == false)
	{
		take_forks(thread);
		do_eat(thread, data);
		if (data->portion_control == true && !thread->to_eat)
			return (NULL);
		do_sleep(thread, data);
		log_message(thread, E_THINK);
	}
	return (NULL);
}

void	do_eat(t_thread *thread, t_data *data)
{
	log_message(thread, E_EAT);
	pthread_mutex_lock(&thread->eat);
	thread->last_meal = thread->timestamp;
	pthread_mutex_unlock(&thread->eat);
	thread->resume = thread->timestamp + data->time_to_eat;
	naomi_sleep(thread, data->time_to_eat);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->to_eat--;
}

void	do_sleep(t_thread *thread, t_data *data)
{
	log_message(thread, E_SLEEP);
	thread->resume = thread->timestamp + data->time_to_sleep;
	naomi_sleep(thread, data->time_to_sleep);
}
