/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/31 17:35:10 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>

static void	*monitor_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	sem_wait(data->death_sem);
	kill_the_children(data);
	return (NULL);
}

static int	create_monitor(t_data *data, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_death, data))
		return (1);
	else if (pthread_detach(*monitor))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		return (log_error(&data, "Incorrect amount or arguments provided", 0));
	if (init_data(&data, argv, argc))
		return (log_error(&data, "Error initialising data", 0));
	if (create_semaphores(&data))
		return (log_error(&data, "Error creating semaphores", 1));
	if (create_monitor(&data, &monitor))
		return (log_error(&data, "Error creating monitoring thread", 2));
	else
	{
		fork_processes(&data);
		unlink_semaphores();
		wait_for_children(&data);
	}
	close_semaphores(&data, false);
	free(data.pid);
	return (0);
}
