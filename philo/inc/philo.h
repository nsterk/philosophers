/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/30 18:26:28 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

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
	int				id;
	int				left_neighbour;
	unsigned long	resume;
	unsigned long	tod;
	unsigned long	timestamp;
	int				times_eaten;
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
	int				death;
}				t_data;

//init
int				init_data(t_data *data, char **argv, int argc);

// thread functions
void			*do_stuff(void *arg);
void			do_sleep(t_thread *thread, t_data *data);
void			do_eat(t_thread *thread, t_data *data);
void			*do_die(t_thread *thread, t_data *data);

// utils
int				ft_atoi(const char *str);
void			usleep_adj(t_thread *thread, long long start_ms);
unsigned long	timestamp(unsigned long start_ms);
void			log_message(t_thread *thread, enum e_msg msg);
int				someone_dead(t_data *data);

#endif