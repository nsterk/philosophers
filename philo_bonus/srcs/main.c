/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/24 15:20:47 by nsterk        ########   odam.nl         */
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

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		return (log_error("Incorrect amount or arguments provided"));
	if (init_data(&data, argv, argc))
		return (log_error("Problem initialising data"));
	create_semaphores(&data);
	if (!pthread_create(&monitor, NULL, monitor_death, &data)
		&& !pthread_detach(monitor))
	{
		fork_processes(&data);
		unlink_semaphores();
		wait_for_children(&data);
	}
	// sem_wait(data.death_sem);
	// kill_the_children(&data);
	close_semaphores(&data, false);
	return (0);
}
