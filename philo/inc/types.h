/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/14 18:00:12 by nsterk        ########   odam.nl         */
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
	E_AMOUNT,
	E_INVALID,
	E_INIT,
	E_THREAD_CREAT,
	E_THREAD_JOIN
};

typedef struct s_thread
{
	pthread_t		tid;
	pthread_t		monitor;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat;
	int				id;
	unsigned long	resume;
	unsigned long	tod;
	unsigned long	timestamp;
	int				to_eat;
	void			*data;
	unsigned long	last_meal;
}				t_thread;

typedef struct s_data
{
	t_thread		*thread;
	pthread_t		monitoring_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	diet_mutex;
	unsigned long	start;
	int				nr_philos;
	int				full_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	bool			death;
	bool			diet;
}				t_data;

#endif