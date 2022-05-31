/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/31 18:19:09 by nsterk        ########   odam.nl         */
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
	if (msg == e_die)
	{
		close_semaphores(data, true);
		exit(0);
	}
	sem_post(data->write_sem);
}

int	log_error(t_data *data, char *str, int stat)
{
	if (stat > 0)
		free(data->pid);
	if (stat > 1)
	{
		unlink_semaphores();
		close_semaphores(data, false);
	}
	printf("%s\n", str);
	return (1);
}

unsigned long	timestamp(unsigned long start_ms)
{
	struct timeval	current;
	unsigned long	current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

void	usleep_adj(t_data *data, unsigned long start_ms)
{
	unsigned long	current_time;

	current_time = timestamp(start_ms);
	while (current_time < data->philo.resume)
	{
		if (current_time >= data->philo.tod)
			do_die(data);
		usleep(100);
		current_time = timestamp(start_ms);
	}
}

void	one_philosopher(t_data *data)
{
	log_message(data, e_fork);
	data->philo.resume = data->philo.tod;
	usleep_adj(data, data->start);
	log_message(data, e_die);
}
