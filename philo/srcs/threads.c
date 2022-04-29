/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/29 18:57:43 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	spawn_threads(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->thread[i].tid, NULL,
				do_stuff, &data->thread[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(data->thread[i].tid, NULL);
		i++;
	}
	return (0);
}

void	*do_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (!(thread->id % 2))
		usleep(1000);
	thread->tod = get_timestamp(data->start) + data->time_to_die;
	while (someone_dead(data) == 0)
	{
		if (get_timestamp(data->start) >= thread->tod)
			return (do_die(thread, data));
		do_eat(thread, data);
		if (log_sleep(thread, data))
			return (NULL);
		log_think(thread, data);
	}
	return (NULL);
}
