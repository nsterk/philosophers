/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphores.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 16:09:24 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/24 14:39:18 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	create_semaphores(t_data *data)
{
	data->fork_sem = sem_open(FORK_SEM, O_CREAT | O_EXCL, 0644, data->nr_philos);
	if (data->fork_sem == SEM_FAILED)
	{
		printf("create fork sem fail\n");
		return (1);
	}
	data->write_sem = sem_open(WRITE_SEM, O_CREAT | O_EXCL, 0644, 1);
	if (data->write_sem == SEM_FAILED)
	{
		printf("create write sem fail\n");
		return (1);
	}
	data->death_sem = sem_open(DEATH_SEM, O_CREAT | O_EXCL, 0644, 0);
	if (data->death_sem == SEM_FAILED)
	{
		printf("create death sem fail\n");
		return (1);
	}
	return (0);
}

void	open_semaphores(t_data *data)
{
	data->fork_sem = sem_open(FORK_SEM, O_RDWR);
	if (data->fork_sem == SEM_FAILED)
	{
		printf("Failure opening fork sem philo %d\n", data->id);
		exit(1);
	}
	data->death_sem = sem_open(DEATH_SEM, O_RDWR);
	if (data->death_sem == SEM_FAILED)
	{
		printf("Failure opening death sem philo %d\n", data->id);
		sem_close(data->fork_sem);
		exit(1);
	}
	data->write_sem = sem_open(WRITE_SEM, O_RDWR);
	if (data->write_sem == SEM_FAILED)
	{
		sem_close(data->fork_sem);
		sem_close(data->death_sem);
		printf("Failure opening write sem philo %d\n", data->id);
		exit(1);
	}
	return ;
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

int	close_semaphores(t_data *data, bool post)
{
	int	ret;

	ret = 0;
	ret |= sem_close(data->write_sem);
	ret |= sem_close(data->fork_sem);
	if (post == true)
		sem_post(data->death_sem);
	ret |= sem_close(data->death_sem);
	return (ret);
}

