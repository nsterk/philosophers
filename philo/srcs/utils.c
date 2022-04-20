/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/16 14:48:10 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 19:09:25 by nsterk        ########   odam.nl         */
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

long long	get_timestamp(long long start_ms)
{
	struct timeval	current;
	long long		current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

/*
void	*check_fatalities(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->death_mutex);
	while (!data->death)
	{
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_lock(&data->death_mutex);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (NULL);
}
*/

void	log_message(t_thread *thread, long timestamp, int state)
{
	t_data	*data;

	data = (t_data *)thread->data;
	pthread_mutex_lock(&data->write_mutex);
	if (state == STATE_EAT)
		printf("%ld %i is eating\n", timestamp, thread->id);
	else if (state == STATE_DEAD)
		printf("%ld %i has died\n", timestamp, thread->id);
	else if (state == STATE_SLEEP)
		printf("%ld %i is sleeping\n", timestamp, thread->id);
	pthread_mutex_unlock(&data->write_mutex);
}
