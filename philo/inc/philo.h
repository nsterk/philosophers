/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/29 17:10:24 by nsterk        ########   odam.nl         */
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
# define FORK1			1
# define FORK2			2
# define EATING			3
# define SLEEPING		4
# define THINKING		5
# define DEAD			6

typedef struct s_thread
{
	pthread_t		tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	// unsigned long	last_meal;
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
	pthread_mutex_t	*status_m;
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
// int			init_threads(t_data *data);
int				spawn_threads(t_data *data);
void			*do_stuff(void *arg);
void			*check_fatalities(void *arg);

void			do_wait(t_thread *thread, long long start_ms);
void			do_eat(t_thread *thread, t_data *data);
void			do_sleep(t_thread *thread, t_data *data);
void			do_think(t_thread *thread, t_data *data);
void			*do_die(t_thread *thread, t_data *data);

void			log_fork(t_thread *thread, t_data *data);
void			log_eat(t_thread *thread, t_data *data);
int				log_sleep(t_thread *thread, t_data *data);
void			log_think(t_thread *thread, t_data *data);

// utils
int				ft_atoi(const char *str);
const char		*ft_skipspace(const char *str);
unsigned long	get_timestamp(unsigned long start_ms);
unsigned long	log_message(t_thread *thread, int state);
int				someone_dead(t_data *data);

// Test
void			print_info(t_data *data);
void			print_fork_addresses(t_data *data);
void			print_thefucking_times(t_thread *thread, unsigned long timestamp);

#endif