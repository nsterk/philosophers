/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 00:38:13 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/29 16:40:00 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (timestamp(0) < data->start)
		usleep(100);
	while (1)
	{
		sem_wait(data->philo.meal_sem);
		if (timestamp(data->start) >= (data->philo.last_meal + \
				data->time_to_die))
			log_message(data, E_DIE);
		sem_post(data->philo.meal_sem);
		usleep(100);
	}
	return (NULL);
}
