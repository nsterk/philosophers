/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/18 16:06:12 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/14 14:06:40 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <sys/time.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i);
}

bool	validate_args(t_data *data, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
			return (false);
		i++;
	}
	data->nr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->diet = false;
	if (argc == 6)
	{
		data->to_eat = ft_atoi(argv[5]);
		data->diet = true;
	}
	else
		data->to_eat = 0;
	if (data->nr_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->to_eat < 0)
		return (false);
	return (true);
}

unsigned long	timestamp(unsigned long start_ms)
{
	struct timeval	current;
	unsigned long	current_ms;

	gettimeofday(&current, NULL);
	current_ms = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (current_ms - start_ms);
}

void	usleep_adj(unsigned long ms)
{
	struct timeval	elapsed;
	unsigned long	elapsed_ms;

	gettimeofday(&elapsed, NULL);
	elapsed_ms = (elapsed.tv_sec * 1000) + (elapsed.tv_usec / 1000);
	while (timestamp(elapsed_ms) < ms)
		usleep(100);
}
