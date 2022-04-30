/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/30 19:20:34 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <types.h>
# include <stdio.h>

int				init_data(t_data *data, char **argv, int argc);

// thread functions
void			*do_stuff(void *arg);
void			*do_stuff_count(void *arg);
void			do_sleep(t_thread *thread, t_data *data);
void			do_eat(t_thread *thread, t_data *data);
void			*do_die(t_thread *thread, t_data *data);

// thread utils
void			log_message(t_thread *thread, enum e_msg msg);
int				someone_dead(t_data *data);

// general utils
int				ft_atoi(const char *str);
void			usleep_adj(t_thread *thread, long long start_ms);
int				log_error(char *str);
unsigned long	timestamp(unsigned long start_ms);

#endif