/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/03 21:53:00 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

void	*do_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (data->nr_philos == 1)
		return (one_philosopher(thread, data));
	if (!(thread->id % 2))
		usleep(1000);
	thread->tod = timestamp(data->start) + data->time_to_die;
	while (someone_dead(data) == false)
	{
		if (timestamp(data->start) >= thread->tod)
			return (do_die(thread, data));
		do_eat(thread, data);
		do_sleep(thread, data);
		log_message(thread, e_think);
	}
	return (NULL);
}

void	*do_stuff_count(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (data->nr_philos == 1)
		return (one_philosopher(thread, data));
	if (!(thread->id % 2))
		usleep(1000);
	thread->tod = timestamp(data->start) + data->time_to_die;
	while (someone_dead(data) == false)
	{
		if (!(thread->to_eat) || timestamp(data->start) >= thread->tod)
			return (do_die(thread, data));
		do_eat(thread, data);
		do_sleep(thread, data);
		log_message(thread, e_think);
	}
	return (NULL);
}

void	do_eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	log_message(thread, e_fork);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, e_fork);
	log_message(thread, e_eat);
	thread->resume = thread->timestamp + data->time_to_eat;
	thread->tod = thread->timestamp + data->time_to_die;
	usleep_adj(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->to_eat--;
}

void	do_sleep(t_thread *thread, t_data *data)
{
	log_message(thread, e_sleep);
	thread->resume = thread->timestamp + data->time_to_sleep;
	usleep_adj(thread, data->start);
}

void	*do_die(t_thread *thread, t_data *data)
{
	thread->resume = thread->tod;
	usleep_adj(thread, data->start);
	log_message(thread, e_die);
	return (NULL);
}
