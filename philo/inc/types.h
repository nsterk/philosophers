/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/04 17:23:30 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include <stdbool.h>

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
	E_SEMAPHORE,
	E_THREAD,
	E_FORK
};

typedef struct s_thread
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	unsigned long	resume;
	unsigned long	tod;
	unsigned long	timestamp;
	int				to_eat;
	void			*data;
	int				status;
}				t_thread;

typedef struct s_data
{
	t_thread		*thread;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	unsigned long	start;
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	bool			death;
}				t_data;

#endif