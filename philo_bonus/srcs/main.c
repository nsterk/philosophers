/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/17 15:05:05 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <signal.h>

static void	kill_the_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (log_error("Incorrect amount or arguments provided"));
	if (init_data(&data, argv, argc))
		return (log_error("Problem initialising data"));
	create_semaphores(&data);
	fork_processes(&data);
	sem_wait(data.death_sem);
	kill_the_children(&data);
	sem_close(data.write_sem);
	sem_close(data.fork_sem);
	close_semaphores(&data);
	sem_unlink(WRITE_SEM);
	sem_unlink(DEATH_SEM);
	sem_unlink(FORK_SEM);
	return (0);
}
