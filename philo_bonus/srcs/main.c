/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/25 03:17:25 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>

static void	*monitor_death(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->death_sem = sem_open(DEATH_SEM, O_RDWR);
	if (data->death_sem != SEM_FAILED)
	{
		sem_wait(data->death_sem);
		kill_the_children(data);
	}
	else
		printf("Failure opening death sem in monitor\n");
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
		return (log_error("Incorrect amount or arguments provided"));
	if (init_data(&data, argv, argc))
		return (log_error("Problem initialising data"));
	create_semaphores(&data);
	if (create_monitor(&data, &monitor))
		unlink_semaphores();
	else
	{
		fork_processes(&data);
		unlink_semaphores();
		// usleep(100);
		wait_for_children(&data);
	}
	// sem_wait(data.death_sem);
	// kill_the_children(&data);
	close_semaphores(&data, false);
	return (0);
}
