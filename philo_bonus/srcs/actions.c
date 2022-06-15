/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 18:02:11 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/15 18:18:40 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	do_stuff(t_data *data)
{
	if (open_semaphores(data))
	{
		printf("Error opening semaphore in child\n");
		exit(1);
	}
	data->philo.last_meal = timestamp(data->start);
	if (data->philo.id % 2)
		usleep(1000);
	while (1)
	{
		do_eat(data);
		if (data->diet == true && !data->philo.to_eat)
		{
			close_semaphores(data, false, false);
			break ;
		}
		do_sleep(data);
		log_message(data, E_THINK);
	}
	exit(0);
}

void	do_eat(t_data *data)
{
	sem_wait(data->fork_sem);
	log_message(data, E_FORK);
	sem_wait(data->fork_sem);
	log_message(data, E_FORK);
	log_message(data, E_EAT);
	// sem_wait adjust last_meal sem_post
	usleep_adj(data, data->start);
	sem_post(data->fork_sem);
	sem_post(data->fork_sem);
	data->philo.to_eat--;
}

void	do_sleep(t_data *data)
{
	log_message(data, E_SLEEP);
	usleep_adj(data, data->time_to_sleep);
}
