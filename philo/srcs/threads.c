/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/27 13:13:58 by nsterk        ########   odam.nl         */
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
		// pthread_detach(data->thread[i].tid);
		i++;
	}
	i = 0;
	while (i < data->nr_philos)
	{
		pthread_join(data->thread[i].tid, NULL);
		i++;
	}
	pthread_create(&monitor, NULL, check_fatalities, data);
	pthread_join(monitor, NULL);
	return (0);
}

void	*monitor(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;

	while (1)
	{
		pthread_mutex_lock(&thread->death_mutex);
		if (thread->tod >= get_timestamp(data->start))
			thread->death = 1;
		pthread_mutex_unlock(&thread->death_mutex);
	}
	return (NULL);
}

void	*do_stuff(void *arg)
{
	t_thread	*thread;
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	// create monitoring thread
	if (!(thread->id % 2))
		usleep(100);
	thread->tod = get_timestamp(data->start) + data->time_to_die;
	while (1)
	{
		if (someone_dead(data))
			break ;
		if (get_timestamp(data->start) >= thread->tod)
		{
			(do_die(thread, data));
		}
		do_eat(thread, data);
		log_sleep(thread, data);
		log_think(thread, data);
	}
	usleep(200);
	// pthread_mutex_unlock(thread->left_fork);
	// pthread_mutex_unlock(thread->right_fork);
	return (NULL);
}

void	*check_fatalities(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (someone_dead(data))
			break ;
	}
	usleep(10000);
	return (NULL);
}

// void	*monitor_count(void *arg)
// {
	
// }
