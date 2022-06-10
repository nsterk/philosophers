/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/07 13:32:56 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
#include <signal.h>

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

	if (argc < 5 || argc > 6 || valid_args(&data, argv, argc) == false)
		log_error(&data, E_INVALID);
	if (init_data(&data))
		log_error(&data, E_INIT);
	if (create_semaphores(&data))
		log_error(&data, E_SEM);
	if (create_monitor(&data, &monitor))
		log_error(&data, E_THREAD);
	if (fork_processes(&data))
		log_error(&data, E_PROCESS);
	wait_for_children(&data);
	unlink_semaphores();
	close_semaphores(&data, false);
	free(data.pid);
	return (0);
}
