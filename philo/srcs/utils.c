/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/30 16:29:09 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static const char	*ft_skipspace(const char *str)
{
	while (*str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\r' || *str == '\v' || *str == ' ')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	new_num;
	int	negative;

	num = 0;
	negative = 1;
	if (*str == '\0')
		return (0);
	str = ft_skipspace(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		new_num = (num * 10) + (*str - '0');
		if (new_num < num)
			return (0);
		num = new_num;
		str++;
	}
	return (num * negative);
}

int	someone_dead(t_data *data)
{
	int	death;

	death = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (data->death)
		death = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (death);
}

unsigned long	get_timestamp(unsigned long start_ms)
{
	struct timeval	current;
	unsigned long	current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

void	log_message(t_thread *thread, enum e_msg msg)
{
	t_data				*data;
	static const char	*msgs[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"died"
	};

	data = (t_data *)thread->data;
	pthread_mutex_lock(&data->write_mutex);
	thread->timestamp = get_timestamp(data->start);
	if (!someone_dead(data))
		printf("%lu %d %s\n", thread->timestamp, thread->id, msgs[msg]);
	if (msg == e_die)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->death = 1;
		pthread_mutex_unlock(&data->death_mutex);
	}
	pthread_mutex_unlock(&data->write_mutex);
}
