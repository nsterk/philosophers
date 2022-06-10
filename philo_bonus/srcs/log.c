/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   log.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/04 20:18:26 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/04 20:19:30 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <sys/time.h>
#include <unistd.h>

void	log_message(t_data *data, enum e_msg msg)
{
	static const char	*msgs[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	sem_wait(data->write_sem);
	data->philo.timestamp = timestamp(data->start);
	printf("%lu %d %s\n", data->philo.timestamp, data->philo.id + 1, msgs[msg]);
	if (msg == E_DIE)
	{
		close_semaphores(data, true);
		exit(0);
	}
	sem_post(data->write_sem);
}

void	log_error(t_data *data, enum e_error err)
{
	static const char	*msgs[] = {
		"Invalid argument(s)",
		"Error initialising data",
		"Error creating semaphores",
		"Error creating thread",
		"Error forking processes, program terminated"
	};

	if (err == E_PROCESS)
	{
		sem_post(data->death_sem);
		usleep(5000);
	}
	printf("%s\n", msgs[err]);
	if (err > E_INIT)
		free(data->pid);
	if (err > E_THREAD)
	{
		unlink_semaphores();
		close_semaphores(data, false);
	}
	exit(1);
}
