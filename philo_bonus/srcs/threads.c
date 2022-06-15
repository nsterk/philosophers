/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 00:38:13 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/15 23:19:45 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->death_sem);
		if (timestamp(data->start) >= (data->philo.last_meal + \
				data->time_to_die))
			log_message(data, E_DIE);
	}
	return (arg);
}
