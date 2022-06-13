/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphores.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 16:09:24 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/13 02:16:24 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	create_semaphores(t_data *data)
{
	unlink_semaphores();
	data->sems[0] = sem_open(DEATH_SEM, O_CREAT | O_EXCL, 0644, 0);
	if (data->sems[0] == SEM_FAILED)
		return (1);
	data->sems[1] = sem_open(WRITE_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (data->sems[1] == SEM_FAILED)
	{
		close_semaphores(data, false, 0, true);
		return (1);
	}
	data->sems[2] = sem_open(FORK_SEM, O_CREAT | O_EXCL, 0644, data->nr_philos);
	if (data->sems[2] == SEM_FAILED)
	{
		close_semaphores(data, false, 1, true);
		return (1);
	}
	data->sems[3] = sem_open(MEAL_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (data->sems[3] == SEM_FAILED)
	{
		close_semaphores(data, false, 2, true);
		return (1);
	}
	return (0);
}

int	open_semaphores(t_data *data)
{
	data->sems[0] = sem_open(DEATH_SEM, O_RDWR);
	if (data->sems[0] == SEM_FAILED)
		return (1);
	data->sems[1] = sem_open(WRITE_SEM, O_RDWR);
	if (data->sems[1] == SEM_FAILED)
	{
		close_semaphores(data, false, 0, false);
		return (1);
	}
	data->sems[2] = sem_open(FORK_SEM, O_RDWR);
	if (data->sems[2] == SEM_FAILED)
	{
		close_semaphores(data, false, 1, false);
		return (1);
	}
	data->sems[3] = sem_open(MEAL_SEM, O_RDWR);
	if (data->sems[3] == SEM_FAILED)
	{
		close_semaphores(data, false, 2, false);
		return (1);
	}
	return (0);
}

int	unlink_semaphores(void)
{
	int	ret;

	ret = 0;
	ret |= sem_unlink(FORK_SEM);
	ret |= sem_unlink(WRITE_SEM);
	ret |= sem_unlink(MEAL_SEM);
	ret |= sem_unlink(DEATH_SEM);
	return (ret);
}

int	close_semaphores(t_data *data, bool post, int index, bool unlink)
{
	int	ret;

	ret = 0;
	if (post == true)
	{
		sem_post(data->sems[0]);
		usleep(1000);
	}
	while (index >= 0)
	{
		ret |= sem_close(data->sems[index]);
		index--;
	}
	if (unlink == true)
		unlink_semaphores();
	return (ret);
}
