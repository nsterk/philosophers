/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/14 18:28:38 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <unistd.h>

static void	*monitor(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (timestamp(0) < data->start)
		usleep(100);
	while (someone_dead(data) == false && philos_full(data) == false)
	{
		i = 0;
		while (i < data->nr_philos)
		{
			pthread_mutex_lock(&data->thread[i].eat);
			if (timestamp(data->start) > (data->thread[i].last_meal + \
							data->time_to_die))
			{
				log_message(&data->thread[i], E_DIE);
				pthread_mutex_unlock(&data->thread[i].eat);
				break ;
			}	
			pthread_mutex_unlock(&data->thread[i].eat);
			i++;
		}
	}
	return (NULL);
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_create(&data->monitoring_thread, NULL, monitor, data))
		return (1);
	while (i < data->nr_philos)
	{
		if (pthread_create(&data->thread[i].tid, NULL,
				do_stuff, &data->thread[i]))
			return (1);
		pthread_detach(data->thread[i].tid);
		i++;
	}
	return (0);
}

// static int	join_threads(t_data *data, int i)
// {
// 	while (i < data->nr_philos)
// 	{
// 		if (pthread_join(data->thread[i].tid, NULL))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (log_error(&data, E_AMOUNT));
	if (validate_args(&data, argv, argc) == false)
		return (log_error(&data, E_INVALID));
	if (data.diet == true && data.to_eat == 0)
		return (0);
	if (init_data(&data))
		return (log_error(&data, E_INIT));
	if (create_threads(&data))
		return (log_error(&data, E_THREAD_CREAT));
	pthread_join(data.monitoring_thread, NULL);
	// if (join_threads(&data, 0))
	// 	return (log_error(&data, E_THREAD_JOIN));
	return (free_memory(&data));
}
