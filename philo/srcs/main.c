/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/19 18:22:55 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

static void	*do_stuff(void *arg)
{
	t_thread *thread	= (t_thread *)arg;
	t_data *data		= (t_data *)thread->data;
	struct timeval end;
	int printed = 0;
	
	pthread_mutex_lock(&data->death_mutex);
	while (1 && !data->death)
	{
		pthread_mutex_unlock(&data->death_mutex);
		gettimeofday(&end, NULL);
		pthread_mutex_lock(&thread->thread_mutex);
		if (!thread->last_meal)
			{
				log_message(thread, get_timestamp(end) - thread->start_ms, STATE_EAT);
				usleep(100000);
			}
		else
		{
			pthread_mutex_lock(&data->death_mutex);
			data->death = 1;
			pthread_mutex_unlock(&data->death_mutex);
			log_message(thread, get_timestamp(end) - thread->start_ms, STATE_DEAD);
			return (NULL);
		}
		pthread_mutex_unlock(&thread->thread_mutex);
		pthread_mutex_lock(&data->death_mutex);
	}
	return (NULL);
}

static int		init_threads(int nr, t_data *data)
{
	int	i;

	data->thread = malloc(sizeof(t_thread) * 2);
	if (!data->thread)
		return (1);
	data->death = 0;
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	i = 0;
	while (i < nr)
	{
		data->thread[i].id = i + 1;
		data->thread[i].last_meal = 0;
		data->thread[i].start_ms = data->start_ms;
		data->thread[i].time_to_die = 150;
		data->thread[i].data = (t_data *)data;
		if (pthread_mutex_init(&data->thread[i].thread_mutex, NULL))
			return (1);
		i++;
	}
	return (0);
}

static int	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pthread_create(&data->thread[i].tid, NULL, do_stuff, &data->thread[i]))
			return (1);
		pthread_detach(data->thread[i].tid);
		usleep(200);
		i++;
	}
	// i = 0;
	// while (i < 2)
	// {
	// 	pthread_join(data->thread[i].tid, NULL);
	// 	i++;
	// }
	return (0);
}

int	main(void)
{
	t_data			data;


	gettimeofday(&data.start, NULL);
	data.start_ms = get_timestamp(data.start);
	init_threads(2, &data);
	pthread_mutex_init(&data.write_mutex, NULL);
	spawn_threads(&data);
	check_fatalities(&data);
	return (0);
}
