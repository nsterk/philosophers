/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/04 17:35:53 by nsterk        ########   odam.nl         */
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

typedef struct s_philo
{
	int				id;
	int				to_eat;
	unsigned long	timestamp;
	unsigned long	tod;
	unsigned long	resume;
}				t_philo;

typedef struct s_data
{
	pid_t			*pid;
	sem_t			*write_sem;
	sem_t			*death_sem;
	sem_t			*fork_sem;
	t_philo			philo;
	unsigned long	start;
	unsigned long	tod;
	unsigned long	timestamp;
	int				id;
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	bool			death;
}				t_data;

#endif