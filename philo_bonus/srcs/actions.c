/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/03 00:36:41 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	do_stuff(t_data *data)
{
	open_semaphores(data);
	data->philo.tod = timestamp(data->start) + data->time_to_die;
	if (data->nr_philos == 1)
		one_philosopher(data);
	if (data->philo.id % 2)
		usleep(50);
	while (1)
	{
		if (timestamp(data->start) >= data->philo.tod)
			do_die(data);
		do_eat(data);
		do_sleep(data);
		log_message(data, e_think);
	}
	exit(0);
}

void	do_stuff_count(t_data *data)
{
	open_semaphores(data);
	data->philo.tod = timestamp(data->start) + data->time_to_die;
	while (1)
	{
		if (timestamp(data->start) >= data->philo.tod)
			do_die(data);
		do_eat(data);
		if (!data->philo.to_eat)
		{
			close_semaphores(data, false);
			break ;
		}
		do_sleep(data);
		log_message(data, e_think);
	}
	exit(0);
}

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
