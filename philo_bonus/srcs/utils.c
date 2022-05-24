/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/24 13:41:58 by nsterk        ########   odam.nl         */
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
		// sem_close(data->write_sem);
		// sem_close(data->fork_sem);
		// sem_post(data->death_sem);
		// sem_close(data->death_sem);
		exit(0);
	}
	sem_post(data->write_sem);
}

int	log_error(char *str)
{
	printf("%s\n", str);
	return (0);
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
