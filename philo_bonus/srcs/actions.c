/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/04 20:26:25 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	do_eat(t_data *data)
{
	sem_wait(data->fork_sem);
	log_message(data, E_FORK);
	sem_wait(data->fork_sem);
	log_message(data, E_FORK);
	log_message(data, E_EAT);
	data->philo.resume = data->philo.timestamp + data->time_to_eat;
	data->philo.tod = data->philo.timestamp + data->time_to_die;
	usleep_adj(data, data->start);
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
	data->philo.to_eat--;
}

void	do_sleep(t_data *data)
{
	log_message(data, E_SLEEP);
	data->philo.resume = data->philo.timestamp + data->time_to_sleep;
	usleep_adj(data, data->start);
}

void	do_die(t_data *data)
{
	data->philo.resume = data->philo.tod;
	usleep_adj(data, data->start);
	log_message(data, E_DIE);
}

void	one_philosopher(t_data *data)
{
	log_message(data, E_FORK);
	data->philo.resume = data->philo.tod;
	usleep_adj(data, data->start);
	log_message(data, E_DIE);
}