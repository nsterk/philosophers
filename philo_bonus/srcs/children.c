/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 14:41:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/24 15:23:35 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <signal.h>

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

int	fork_processes(t_data *data)
{
	while (data->philo.id < data->nr_philos)
	{
		data->pid[data->philo.id] = fork();
		if (data->pid[data->philo.id] < 0)
			return (1);
		if (data->pid[data->philo.id] == 0)
		{
			if (data->philo.to_eat)
				do_stuff_count(data);
			else
				do_stuff(data);
		}
		data->philo.id++;
	}
	return (0);
}
