/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 16:05:46 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define FREE			0
# define EATING			1
# define SLEEPING		2
# define THINKING		3
# define DEAD			4

typedef struct s_thread
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				state;
	int				hungry;
	long			last_meal;
	long			continue_time;
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
	int				death;
}				t_data;

//init
int			init_data(t_data *data, char **argv, int argc);

// thread functions
// int			init_threads(t_data *data);
int			spawn_threads(t_data *data);
void		*do_stuff(void *arg);
void		eat(t_thread *thread, t_data *data);
void		*check_fatalities(void *arg);

// utils
int			ft_atoi(const char *str);
const char	*ft_skipspace(const char *str);
long long	get_timestamp(long long start_ms);
void		log_message(t_thread *thread, int state);

// Test
void		print_info(t_data *data);
void		print_fork_addresses(t_data *data);

#endif