/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 15:33:28 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	*do_stuff(void *arg)
{
	t_thread *thread	= (t_thread *)arg;
	t_data *data		= (t_data *)thread->data;
	struct timeval end;
	
	if (!thread->id % 2)
		usleep(1000);
	while (1)
	{
		if (!thread->times_eaten)
			{
				log_message(thread, get_timestamp(thread->start_ms), STATE_EAT);
				thread->times_eaten++;
				usleep(100000);
			}
		else
		{
			log_message(thread, get_timestamp(thread->start_ms), STATE_DEAD);
			break ;
		}
	}
	return (NULL);
}

static int	spawn_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (pthread_create(&data->thread[i].tid, NULL, do_stuff, &data->thread[i]))
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

static int	get_arguments(t_data *data, char **argv, int argc)
{
	data->nr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->to_eat = ft_atoi(argv[5]);
	else
		data->to_eat = 0;
	if (data->nr_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->to_eat < 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect nr of arguments provided\n");
		return (0);
	}
	if (get_arguments(&data, argv, argc))
		return (0);
	printf("nr_philosophers: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep: %d\nto_eat: %d\n", data.nr_philos,
		data.time_to_die, data.time_to_eat, data.time_to_sleep, data.to_eat);
	// init_threads(2, &data);
	// pthread_mutex_init(&data.write_mutex, NULL);
	// spawn_threads(&data);
	return (0);
}
