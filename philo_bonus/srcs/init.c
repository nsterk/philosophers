/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/31 16:43:18 by nsterk        ########   odam.nl         */
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
		data->philo.to_eat = ft_atoi(argv[5]);
	else
		data->philo.to_eat = 0;
	if (data->nr_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || data->philo.to_eat < 0)
		return (1);
	data->pid = malloc(sizeof(pid_t) * data->nr_philos);
	if (!data->pid)
		return (1);
	data->philo.id = 0;
	data->philo.resume = 0;
	data->start = timestamp(0);
	data->philo.timestamp = data->start;
	return (0);
}
