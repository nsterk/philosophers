/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_children.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 22:38:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/15 02:19:25 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

/*
init_child
	create sem_name
	open_sem
fork_process
close sem
unlink sem
free sem_name
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
	if (philo->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	init_child(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * 1);
	if (!data->philo)
		return (1);
	if (init_child(data->philo))
		return (1);
	return (0);
}
