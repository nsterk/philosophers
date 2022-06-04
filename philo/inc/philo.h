/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/03 00:22:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <types.h> 
# include <stdio.h>

int				init_data(t_data *data);
int				init_mutexes(t_data *data);

// thread functions
void			*do_stuff(void *arg);
void			*do_stuff_count(void *arg);
void			do_sleep(t_thread *thread, t_data *data);
void			do_eat(t_thread *thread, t_data *data);
void			*do_die(t_thread *thread, t_data *data);

// thread utils
void			log_message(t_thread *thread, enum e_msg msg);
bool			someone_dead(t_data *data);

// general utils
int				ft_atoi(const char *str);
int				free_memory(t_data *data);
void			usleep_adj(t_thread *thread, long long start_ms);
int				log_error(t_data *data, char *str, int stat);
unsigned long	timestamp(unsigned long start_ms);

// edge case
void			*one_philosopher(t_thread *thread, t_data *data);

#endif