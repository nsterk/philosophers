/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 20:21:25 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	be_busy(t_thread *thread, long long start_ms)
{
	while (get_timestamp(start_ms) < thread->resume)
		usleep(50);
	thread->state = FREE;
}

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
		if ((int)(get_timestamp(data->start) - thread->last_meal) <= data->time_to_die)
		{
			eat(thread, data);
			log_message(thread, SLEEPING);
			be_busy(thread, data->start);
			log_message(thread, THINKING);
		}
		else
		{
			thread->resume = thread->last_meal + data->time_to_die;
			be_busy(thread, data->start);
			log_message(thread, DEAD);
			break ;
		}
	}
	return (NULL);
}

void	eat(t_thread *thread, t_data *data)
{
	pthread_mutex_lock(thread->left_fork);
	log_message(thread, FORK);
	pthread_mutex_lock(thread->right_fork);
	log_message(thread, FORK);
	log_message(thread, EATING);
	thread->resume = thread->last_meal + data->time_to_eat;
	be_busy(thread, data->start);
	pthread_mutex_unlock(thread->left_fork);
	pthread_mutex_unlock(thread->right_fork);
	thread->times_eaten++;
	return ;
}

/*
AVOID USLEEP by setting thread to busy and free. redesign the routine

if (state == FREE)
	if (get_timestamp >= thread->continue_time)
		state = free
else
	if (hungry && enough time)
	{
		log eat --> daarin kan continue time = timestamp + time_to_eat
		state = busy
		hungry = 0
		last_meal = timestamp
	}
	else if (enough time)
	{
		log sleep --> daarin kan continue time = timestamp + time_to_sleep
		state = busy
		hungry = 1
	}
 */
int	spawn_threads(t_data *data)
{
	int			i;
	int			ret;
	pthread_t	monitor;

	i = 0;
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->thread[i].tid, NULL,
				do_new_stuff, &data->thread[i]))
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
