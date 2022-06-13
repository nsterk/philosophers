/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/24 14:41:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/13 02:10:13 by nsterk        ########   odam.nl         */
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
			do_stuff(data);
		data->philo.id++;
	}
	usleep(500);
	return (0);
}

void	do_stuff(t_data *data)
{
	if (open_semaphores(data))
	{
		printf("Error opening semaphore in child\n");
		exit(1);
	}
	data->philo.tod = timestamp(data->start) + data->time_to_die;
	if (data->nr_philos == 1)
		one_philosopher(data);
	if (data->philo.id % 2)
		usleep(1000);
	while (1)
	{
		if (timestamp(data->start) >= data->philo.tod)
			do_die(data);
		do_eat(data);
		if (data->portion_control == true && !data->philo.to_eat)
		{
			close_semaphores(data, false, 3, false);
			break ;
		}
		do_sleep(data);
		log_message(data, E_THINK);
	}
	exit(0);
}
