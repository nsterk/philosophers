/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/23 19:02:10 by nsterk        ########   odam.nl         */
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
# define FORK			1
# define EATING			2
# define SLEEPING		3
# define THINKING		4
# define DEAD			5

typedef struct s_thread
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				state;
	int				hungry;
	unsigned long	last_meal;
	unsigned long	resume;
	unsigned long	tod;
	int				time_to_die;
	int				times_eaten;
	void			*data;
}				t_thread;

typedef struct s_data
{
	t_thread		*thread;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
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
// int			init_threads(t_data *data);
int				spawn_threads(t_data *data);
void			*do_stuff(void *arg);
void			eat(t_thread *thread, t_data *data);
void			*check_fatalities(void *arg);

void			*do_new_stuff(void *arg);
void			be_busy(t_thread *thread, long long start_ms);
void			do_eating(t_thread *thread, t_data *data);
void			do_sleeping(t_thread *thread, t_data *data);
void			do_thinking(t_thread *thread, t_data *data);
void			*do_dying(t_thread *thread, t_data *data);

// utils
int				ft_atoi(const char *str);
const char		*ft_skipspace(const char *str);
unsigned long	get_timestamp(unsigned long start_ms);
unsigned long	log_message(t_thread *thread, int state);

// Test
void			print_info(t_data *data);
void			print_fork_addresses(t_data *data);
void			print_thefucking_times(t_thread *thread, unsigned long timestamp);

#endif