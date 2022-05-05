/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/05 20:39:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

// void	*do_stuff(void *arg)
// {
// 	t_thread	*thread;
// 	t_data		*data;

// 	thread = (t_thread *)arg;
// 	data = (t_data *)thread->data;
// 	if (data->nr_philos == 1)
// 		return (one_philosopher(thread, data));
// 	if (!(thread->id % 2))
// 		usleep(1000);
// 	thread->tod = timestamp(data->start) + data->time_to_die;
// 	while (someone_dead(data) == false)
// 	{
// 		if (timestamp(data->start) >= thread->tod)
// 			return (do_die(thread, data));
// 		do_eat(thread, data);
// 		do_sleep(thread, data);
// 		log_message(thread, e_think);
// 	}
// 	return (NULL);
// }

void	do_stuff(t_data *data)
{
	int	i;

	data->write_sem = sem_open(WRITE_SEM, O_RDWR);
	data->death_sem = sem_open(DEATH_SEM, O_RDWR);
	data->fork_sem = sem_open(FORK_SEM, O_RDWR);
	i = 0;
	data->philo.tod = timestamp(data->start) + data->time_to_die;
	while (1)
	{
		if (timestamp(data->start) >= data->philo.tod)
			do_die(data);
		do_eat(data);
		do_sleep(data);
		log_message(data, e_think);
		if (i == data->philo.to_eat)
			break ;
		// sem_post(data->write_sem);
	}
	sem_post(data->death_sem);
	exit(0);
}

// void	*do_stuff_count(void *arg)
// {
// 	t_thread	*thread;
// 	t_data		*data;

// 	thread = (t_thread *)arg;
// 	data = (t_data *)thread->data;
// 	if (data->nr_philos == 1)
// 		return (one_philosopher(thread, data));
// 	if (!(thread->id % 2))
// 		usleep(1000);
// 	thread->tod = timestamp(data->start) + data->time_to_die;
// 	while (someone_dead(data) == false)
// 	{
// 		if (!(thread->to_eat) || timestamp(data->start) >= thread->tod)
// 			return (do_die(thread, data));
// 		do_eat(thread, data);
// 		do_sleep(thread, data);
// 		log_message(thread, e_think);
// 	}
// 	return (NULL);
// }

void	do_eat(t_data *data)
{
	sem_wait(data->fork_sem);
	log_message(data, e_fork);
	sem_wait(data->fork_sem);
	log_message(data, e_fork);
	log_message(data, e_eat);
	data->philo.resume = data->philo.timestamp + data->time_to_eat;
	data->philo.tod = data->philo.timestamp + data->time_to_die;
	usleep_adj(data, data->start);
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
	data->philo.to_eat--;
}
// void	do_eat(t_thread *thread, t_data *data)
// {
// 	pthread_mutex_lock(thread->left_fork);
// 	log_message(thread, e_fork);
// 	pthread_mutex_lock(thread->right_fork);
// 	log_message(thread, e_fork);
// 	log_message(thread, e_eat);
// 	thread->resume = thread->timestamp + data->time_to_eat;
// 	thread->tod = thread->timestamp + data->time_to_die;
// 	usleep_adj(thread, data->start);
// 	pthread_mutex_unlock(thread->left_fork);
// 	pthread_mutex_unlock(thread->right_fork);
// 	thread->to_eat--;
// }

void	do_sleep(t_data *data)
{
	log_message(data, e_sleep);
	data->philo.resume = data->philo.timestamp + data->time_to_sleep;
	usleep_adj(data, data->start);
}

void	do_die(t_data *data)
{
	data->philo.resume = data->philo.tod;
	usleep_adj(data, data->start);
	log_message(data, e_die);
}
