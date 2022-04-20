/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 16:23:53 by nsterk        ########   odam.nl         */
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	long			last_meal;
	int				time_to_die;
	int				times_eaten;
	void			*data;
}				t_thread;

typedef struct s_data
{
	t_thread		*thread;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	long long		start_ms;
	int				nr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
}				t_data;

// thread functions
int			init_threads(t_data *data);
int			spawn_threads(t_data *data);
void		*do_stuff(void *arg);
void		*check_fatalities(void *arg);

// utils
int			ft_atoi(const char *str);
const char	*ft_skipspace(const char *str);
long long	get_timestamp(long long start_ms);
void		log_message(t_thread *thread, long timestamp, int state);

// Test
void	print_info(t_data *data);

#endif