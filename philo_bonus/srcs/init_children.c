/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_children.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 22:38:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/13 22:43:40 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	create_meal_sem(t_philo *philo)
{
	philo->meal_sem_name = ft_itoa(philo->id);
	if (!philo->meal_sem_name)
		return (1);
	sem_unlink(philo->meal_sem);
	philo->meal_sem = sem_open(philo->meal_sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	init_child(t_data *data)
{
	return (0);
}
