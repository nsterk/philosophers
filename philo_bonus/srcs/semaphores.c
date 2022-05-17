/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semaphores.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 16:09:24 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/17 16:36:51 by nsterk        ########   odam.nl         */
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

int	open_sem_wrap(sem_t *sem, char *addr)
{
	sem = sem_open(addr, O_RDWR);
	if (sem == SEM_FAILED)
	{
		printf("Failure opening %s\n", addr);
		return (1);
	}
	return (0);
}

int	close_semaphores(t_data *data)
{
	int	ret;

	ret = 0;
	// ret |= sem_close(data->write_sem);
	ret |= sem_close(data->death_sem);
	// ret |= sem_close(data->fork_sem);
	return (ret);
}

