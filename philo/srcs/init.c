/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 14:27:23 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

int	init_threads(int nr, t_data *data)
{
	int			i;
	long long	start_ms;

	gettimeofday(&data->start, NULL);
	start_ms = get_timestamp(0);
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
		data->thread[i].times_eaten = 0;
		data->thread[i].start_ms = start_ms;
		data->thread[i].time_to_die = 150;
		data->thread[i].data = (t_data *)data;
		if (pthread_mutex_init(&data->thread[i].thread_mutex, NULL))
			return (1);
		i++;
	}
	return (0);
}
