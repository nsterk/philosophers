/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 18:50:21 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

const char	*ft_skipspace(const char *str)
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

unsigned long	get_timestamp(unsigned long start_ms)
{
	struct timeval	current;
	unsigned long	current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

void	*check_fatalities(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (data->death)
			return (NULL);
	}
	return (NULL);
}

unsigned long	log_message(t_thread *thread, int state)
{
	t_data			*data;
	unsigned long	timestamp;

	data = (t_data *)thread->data;
	if (data->death)
		return (0);
	pthread_mutex_lock(&data->write_mutex);
	timestamp = get_timestamp(data->start);
	if (state == EATING)
		printf("%lu %i is eating\n", timestamp, thread->id);
	else if (state == DEAD)
	{
		data->death = 1;
		printf("%lu %i died\n", timestamp, thread->id);
		return (timestamp);
	}
	else if (state == SLEEPING)
		printf("%lu %i is sleeping\n", timestamp, thread->id);
	else if (state == THINKING)
		printf("%lu %i is thinking\n", timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
	return (timestamp);
}
