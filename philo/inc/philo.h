/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/19 18:57:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h> 

# define STATE_EAT		0
# define STATE_SLEEP	1
# define STATE_THINK	2
# define STATE_DEAD		3

typedef struct s_thread
{
	pthread_t		tid;
	int				id;
	long			last_meal;
	long long		start_ms;
	int				time_to_die;
	int				times_eaten;
	pthread_mutex_t	thread_mutex;
	void			*data;
}				t_thread;

typedef struct s_data
{
	struct timeval	start;
	t_thread		*thread;
	pthread_t		monitor;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	int				death;
	long long		start_ms;
	int				time_to_die;
	int				i;
}				t_data;

long long	get_timestamp(struct timeval time);
void		*check_fatalities(void *arg);
void		log_message(t_thread *thread, long timestamp, int state);

#endif