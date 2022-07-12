/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_children.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 22:38:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/04 11:43:26 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <pthread.h>

static void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (timestamp(0) < data->start)
		usleep(100);
	while (1)
	{
		sem_wait(data->philo.meal_sem);
		if (timestamp(data->start) >= (data->philo.last_meal + \
				data->time_to_die))
			log_message(data, E_DIE);
		sem_post(data->philo.meal_sem);
		usleep(100);
	}
	return (NULL);
}

static int	create_meal_sem(t_philo *philo)
{
	char	*philo_id;

	philo_id = ft_itoa(philo->id);
	if (!philo_id)
		return (1);
	philo->meal_sem_name = ft_strjoin("/philo_", philo_id);
	free(philo_id);
	if (!philo->meal_sem_name)
		return (1);
	philo->meal_sem = sem_open(philo->meal_sem_name, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(philo->meal_sem_name);
	free(philo->meal_sem_name);
	if (philo->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

void	init_child(t_data *data)
{
	if (create_meal_sem(&data->philo))
		exit(E_PROCESS);
	if (pthread_create(&data->philo.monitor_tid, NULL, monitor, data))
		exit(E_PROCESS);
	do_stuff(data);
}
