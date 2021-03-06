/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/12 13:58:45 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <stdbool.h>
# include <unistd.h>
# include <semaphore.h>

# define WRITE_SEM "/writesem"
# define DEATH_SEM "/deathsem"
# define FORK_SEM "/forksem"

enum e_msg
{
	E_FORK,
	E_EAT,
	E_SLEEP,
	E_THINK,
	E_DIE
};

enum e_error
{
	E_INVALID,
	E_INIT,
	E_SEM,
	E_THREAD,
	E_PROCESS
};

enum e_status
{
	E_FULL,
	E_DEAD
};

typedef struct s_philo
{
	int				id;
	pthread_t		monitor_tid;
	sem_t			*meal_sem;
	char			*meal_sem_name;
	int				to_eat;
	unsigned long	timestamp;
	unsigned long	last_meal;
}				t_philo;

typedef struct s_data
{
	pid_t			*pid;
	sem_t			*write_sem;
	sem_t			*death_sem;
	sem_t			*fork_sem;
	t_philo			philo;
	unsigned long	start;
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	bool			diet;
}				t_data;

#endif