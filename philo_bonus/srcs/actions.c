/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/29 18:19:05 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	do_stuff(t_data *data)
{
	while (timestamp(0) < data->start)
		usleep(100);
	if (data->philo.id % 2)
		usleep(1000);
	while (1)
	{
		do_eat(data);
		if (data->diet == true && !data->philo.to_eat)
			exit(E_FULL);
		do_sleep(data);
		log_message(data, E_THINK);
	}
}

void	do_eat(t_data *data)
{
	sem_wait(data->fork_sem);
	log_message(data, E_FORK);
	sem_wait(data->fork_sem);
	log_message(data, E_FORK);
	log_message(data, E_EAT);
	sem_wait(data->philo.meal_sem);
	data->philo.last_meal = data->philo.timestamp;
	sem_post(data->philo.meal_sem);
	usleep_adj(data->time_to_eat);
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
	data->philo.to_eat--;
}

void	do_sleep(t_data *data)
{
	log_message(data, E_SLEEP);
	usleep_adj(data->time_to_sleep);
}
