/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphores.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 16:09:24 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/12 13:59:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	create_semaphores(t_data *data)
{
	unlink_semaphores();
	data->death_sem = sem_open(DEATH_SEM, O_CREAT | O_EXCL, 0644, 0);
	if (data->death_sem == SEM_FAILED)
		return (1);
	data->write_sem = sem_open(WRITE_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (data->write_sem == SEM_FAILED)
	{
		close_semaphores(data, true);
		return (1);
	}
	data->fork_sem = sem_open(FORK_SEM, O_CREAT | O_EXCL, 0644, \
		data->nr_philos);
	if (data->fork_sem == SEM_FAILED)
	{
		close_semaphores(data, true);
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
	ret |= sem_unlink(DEATH_SEM);
	return (ret);
}

int	close_semaphores(t_data *data, bool unlink)
{
	int	ret;

	ret = 0;
	ret |= sem_close(data->death_sem);
	ret |= sem_close(data->write_sem);
	ret |= sem_close(data->fork_sem);
	if (unlink == true)
		unlink_semaphores();
	return (ret);
}
