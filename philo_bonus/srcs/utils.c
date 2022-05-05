/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/05 17:16:55 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <sys/time.h>
#include <unistd.h>

// void	log_message(t_thread *thread, enum e_msg msg)
// {
// 	t_data				*data;
// 	static const char	*msgs[] = {
// 		"has taken a fork",
// 		"is eating",
// 		"is sleeping",
// 		"is thinking",
// 		"died"
// 	};

// 	data = (t_data *)thread->data;
// 	pthread_mutex_lock(&data->write_mutex);
// 	thread->timestamp = timestamp(data->start);
// 	if (someone_dead(data) == false)
// 		printf("%lu %d %s\n", thread->timestamp, thread->id, msgs[msg]);
// 	if (msg == e_die)
// 	{
// 		pthread_mutex_lock(&data->death_mutex);
// 		data->death = true;
// 		pthread_mutex_unlock(&data->death_mutex);
// 	}
// 	pthread_mutex_unlock(&data->write_mutex);
// }

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

// void	usleep_adj(t_thread *thread, long long start_ms)
// {
// 	t_data	*data;

// 	data = (t_data *)thread->data;
// 	while (timestamp(start_ms) < thread->resume && !someone_dead(data))
// 		usleep(100);
// }
