/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/05 19:10:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdlib.h>
#include <signal.h>

void	do_the_thing(t_data *data)
{
	int	i;

	data->write_sem = sem_open(WRITE_SEM, O_RDWR);
	data->death_sem = sem_open(DEATH_SEM, O_RDWR);
	i = 0;
	while (i++ < data->to_eat)
	{
		sem_wait(data->write_sem);
		if (data->id == 0)
			printf("\033[35m");
		else if (data->id == 1)
			printf("\033[36m");
		else if (data->id == 2)
			printf("\033[32m");
		printf("%lu philo %d iteration %d\n", timestamp(data->start), data->id + 1, i);
		printf("\033[0m");
		if (i == data->to_eat)
			break ;
		sem_post(data->write_sem);
		usleep(100);
	}
	sem_close(data->write_sem);
	sem_post(data->death_sem);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (log_error("Incorrect amount or arguments provided\n"));
	if (init_data(&data, argv, argc))
		return (log_error("Problem initialising data\n"));
	create_semaphores(&data);
	fork_processes(&data);
	// data.pid[0] = fork();
	// if (data.pid[0] == 0)
	// 	do_the_thing(&data);
	// data.id++;
	// data.pid[1] = fork();
	// if (data.pid[1] == 0)
	// 	do_the_thing(&data);
	sem_close(data.write_sem);
	sem_wait(data.death_sem);
	kill(data.pid[0], SIGKILL);
	kill(data.pid[1], SIGKILL);
	sem_close(data.death_sem);
	sem_unlink(WRITE_SEM);
	sem_unlink(DEATH_SEM);
	return (0);
}
