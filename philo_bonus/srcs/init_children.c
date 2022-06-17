/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_children.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 22:38:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/17 19:03:16 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>
/*
init_child
	create sem_name
	open_sem
fork_process
close sem
unlink sem
free sem_name
increment philo_id
*/

int	create_meal_sem(t_philo *philo)
{
	char	*philo_id;

	philo_id = ft_itoa(philo->id);
	if (!philo_id)
		return (1);
	philo->meal_sem_name = ft_strjoin("/philo_", philo_id);
	free(philo_id);
	if (!philo->meal_sem_name)
		return (1);
	sem_unlink(philo->meal_sem_name);
	philo->meal_sem = sem_open(philo->meal_sem_name, O_CREAT | O_EXCL, 0644, 1);
	free(philo->meal_sem_name);
	if (philo->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	create_monitor(t_data *data)
{
	if (pthread_create(&data->philo.monitor_tid, NULL, monitor, data))
		return (1);
	if (pthread_detach(data->philo.monitor_tid))
		return (1);
}

int	philo_cleanup(t_data *data)
{
	sem_close(philo->meal_sem);
}

int	init_child(t_data *data)
{
	if (create_meal_sem(&data->philo))
		exit(E_PROCESS);
	data->philo.last_meal = timestamp(data->start);
	if (create_monitor(data))
		exit(E_PROCESS);
	return (0);
}
