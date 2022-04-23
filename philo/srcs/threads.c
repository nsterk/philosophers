/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 20:42:16 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	spawn_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->thread[i].tid, NULL,
				do_stuff, &data->thread[i]))
			return (1);
		pthread_detach(data->thread[i].tid);
		i++;
	}
	pthread_create(&monitor, NULL, check_fatalities, data);
	pthread_join(monitor, NULL);
	return (0);
}

void	*do_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (!thread->id % 2)
		usleep(100);
	thread->tod = get_timestamp(data->start) + data->time_to_die;
	while (!data->death)
	{
		if (get_timestamp(data->start) >= thread->tod)
			return (do_die(thread, data));
		do_eat(thread, data);
		do_sleep(thread, data);
		do_think(thread, data);
	}
	return (NULL);
}

void	*check_fatalities(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->death)
			return (NULL);
	}
	return (NULL);
}
