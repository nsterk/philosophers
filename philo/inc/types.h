/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/03 16:01:05 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>

# define EATING	1

enum e_msg
{
	e_fork,
	e_eat,
	e_sleep,
	e_think,
	e_die
};

typedef struct s_thread
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*state;
	pthread_mutex_t	*left_neighbour;
	pthread_mutex_t	*right_neighbour;
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
	pthread_mutex_t	*states;
	pthread_mutex_t	death_mutex;
	unsigned long	start;
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	int				death;
}				t_data;

#endif