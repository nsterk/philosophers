/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/17 17:12:41 by nsterk        ########   odam.nl         */
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

# define PINK "\033[35m"
# define BLUE "\033[36m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define RESET_COLOUR "\033[0m"

enum e_msg
{
	e_fork,
	e_eat,
	e_sleep,
	e_think,
	e_die
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