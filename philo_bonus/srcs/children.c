/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 14:41:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/29 16:44:51 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <signal.h>

int	fork_processes(t_data *data)
{
	data->start = timestamp(0) + (unsigned long)data->nr_philos + 1;
	data->philo.last_meal = 0;
	while (data->philo.id < data->nr_philos)
	{
		data->pid[data->philo.id] = fork();
		if (data->pid[data->philo.id] < 0)
			return (1);
		if (data->pid[data->philo.id] == 0)
			init_child(data);
		data->philo.id++;
	}
	return (0);
}

void	kill_the_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		kill(data->pid[i], SIGKILL);
		i++;
	}
}

// in any case: waitpid(-1, null, 0) (dus de -1) waits for any child process to end.

void	wait_for_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
	sem_post(data->death_sem);
}
