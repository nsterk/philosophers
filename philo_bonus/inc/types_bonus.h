/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/05 18:00:55 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <stdbool.h>
# include <unistd.h>
# include <semaphore.h>

# define WRITE_SEM "/writesem"
# define DEATH_SEM "/deathsem"

enum e_msg
{
	e_fork,
	e_eat,
	e_sleep,
	e_think,
	e_die
};

typedef struct s_data
{
	unsigned long	start;
	pid_t			*pid;
	sem_t			*write_sem;
	sem_t			*death_sem;
	int				nr_philos;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	bool			death;
}				t_data;

#endif