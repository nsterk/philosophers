/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/05 19:11:08 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdlib.h>

int	init_data(t_data *data, char **argv, int argc)
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
	data->id = 0;
	data->pid = malloc(sizeof(pid_t) * data->nr_philos);
	data->death = 0;
	data->start = timestamp(0);
	return (0);
}

int	create_semaphores(t_data *data)
{
	data->write_sem = sem_open(WRITE_SEM, O_CREAT, 0644, 1);
	if (data->write_sem == SEM_FAILED)
		return (1);
	data->death_sem = sem_open(DEATH_SEM, O_CREAT, 0644, 0);
	if (data->death_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	fork_processes(t_data *data)
{
	while (data->id < data->nr_philos)
	{
		data->pid[data->id] = fork();
		if (data->pid[data->id] < 0)
			return (1);
		if (data->pid[data->id] == 0)
			do_the_thing(data);
		data->id++;
	}
	return (0);
}
