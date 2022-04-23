/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/21 03:47:33 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*do_stuff(void *arg)
{
	t_thread	*thread;	
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (!thread->id % 2)
		usleep(100);
	while (1)
	{
		if (data->death)
			return (NULL);
		if ((get_timestamp(data->start_ms) - thread->last_meal) <= data->time_to_die)
		{
			eat(thread, data);
			log_message(thread, STATE_SLEEP);
			usleep(data->time_to_sleep * 1000);
			log_message(thread, STATE_THINK);
		}
		else
		{
			log_message(thread, STATE_DEAD);
			break ;
		}
	}
	return (NULL);
}

void	eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, STATE_EAT);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
	return ;
}

int	spawn_threads(t_data *data)
{
	int			i;
	int			ret;
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
	ret = 1;
	pthread_create(&monitor, NULL, check_fatalities, data);
	pthread_join(monitor, NULL);
	// i = 0;
	// while (i < data->nr_philos && ret)
	// {
	// 	pthread_join(data->thread[i].tid, (void *)&ret);
	// 	printf("ret thread %d: %d\n", data->thread[i].id, ret);
	// 	i++;
	// }
	return (0);
}
