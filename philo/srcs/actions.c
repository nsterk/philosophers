/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/10 21:08:54 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

void	*monitor_thread(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	while (someone_dead(data) == false)
	{
		if (time_to_die(data, thread) == true)
		{
			log_message(thread, E_DIE);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}

void	*do_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (data->nr_philos == 1)
		return (one_philosopher(thread, data));
	// if (create_monitor(data, thread))
	// 	return (NULL);
	if (!(thread->id % 2))
		usleep(100);
	while (someone_dead(data) == false)
	{
		// if (timestamp(data->start) >= thread->tod)
		// 	return (do_die(thread, data));
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
	// printf("\033[35m BEFORE FIRST FORK	thread %d	last_meal: %lu	timestamp: %lu\033[0m\n", thread->id, thread->last_meal, thread->timestamp);
	pthread_mutex_lock(thread->left_fork);
	// printf("\033[35m AFTER FIRST FORK	thread %d	last_meal: %lu	timestamp: %lu\033[0m\n", thread->id, thread->last_meal, thread->timestamp);
	log_message(thread, E_FORK);
	// printf("\033[35m BEFORE SECOND FORK	thread %d	last_meal: %lu	timestamp: %lu\033[0m\n", thread->id, thread->last_meal, thread->timestamp);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, E_FORK);
	// printf("\033[35m AFTER SECOND FORK	thread %d	last_meal: %lu	timestamp: %lu\033[0m\n", thread->id, thread->last_meal, thread->timestamp);
	log_message(thread, E_EAT);
	pthread_mutex_lock(&thread->eat);
	thread->last_meal = thread->timestamp;
	pthread_mutex_unlock(&thread->eat);
	// printf("\033[35m RIGHT AFTER EAT	thread %d	last_meal: %lu	timestamp: %lu\033[0m\n", thread->id, thread->last_meal, thread->timestamp);
	thread->resume = thread->timestamp + data->time_to_eat;
	naomi_sleep(thread, data->time_to_eat);
	// usleep_adj(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->to_eat--;
}

void	do_sleep(t_thread *thread, t_data *data)
{
	log_message(thread, E_SLEEP);
	thread->resume = thread->timestamp + data->time_to_sleep;
	usleep_adj(thread, data->start);
}

void	*do_die(t_thread *thread, t_data *data)
{
	thread->resume = thread->tod;
	usleep_adj(thread, data->start);
	log_message(thread, E_DIE);
	return (NULL);
}
