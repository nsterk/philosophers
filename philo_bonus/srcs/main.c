/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/14 13:54:47 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
#include <signal.h>

static int	init_data(t_data *data)
{
	data->pid = malloc(sizeof(pid_t) * data->nr_philos);
	if (!data->pid)
		return (1);
	data->philo.id = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc < 5 || argc > 6 || valid_args(&data, argv, argc) == false)
		log_error(&data, E_INVALID);
	if (init_data(&data))
		log_error(&data, E_INIT);
	if (create_semaphores(&data))
		log_error(&data, E_SEM);
	if (fork_processes(&data))
		log_error(&data, E_PROCESS);
	close_semaphores(&data, true);
	wait_for_children(&data);
	free(data.pid);
	return (0);
}
