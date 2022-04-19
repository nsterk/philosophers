/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/19 15:40:28 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	get_timestamp(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	check_fatalities(t_data *data)
{
	int	i;
	int printed = 0;

	while (1)
	{
		i = 0;
		while (i < 2)
		{
			if (!printed)
				printf("\033[36mCHECK_FATALITIES address mutex thread %i: %p\n\033[0m", i + 1, &data->death_mutex[i]);
			pthread_mutex_lock(&data->death_mutex[i]);
			if (data->thread[i].dead)
				return ;
			pthread_mutex_unlock(&data->death_mutex[i]);
			i++;
		}
		printed = 1;
	}
	return ;
}

void	log_message(t_thread *thread, long timestamp, int state)
{
	t_data	*data;

	data = (t_data *)thread->data;
	thread->last_meal = timestamp;
	pthread_mutex_lock(&data->write_mutex);
	if (state == STATE_EAT)
		printf("%ld %i is eating\n", timestamp, thread->id);
	else if (state == STATE_DEAD)
		printf("%ld %i has died\n", timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
}
