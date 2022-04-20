/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:13:19 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 16:22:11 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
#include <stdlib.h>

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_philos)
	{
		data->thread[i].id = i + 1;
		data->thread[i].last_meal = 0;
		data->thread[i].times_eaten = 0;
		data->thread[i].data = (t_data *)data;
		i++;
	}
	return (0);
}
