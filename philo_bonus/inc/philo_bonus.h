/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/17 16:36:24 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <types_bonus.h>
# include <stdio.h>
# include <stdlib.h>

int				init_data(t_data *data, char **argv, int argc);

// thread functions
void			do_stuff(t_data *data);
// void			*do_stuff(void *arg);
// void			*do_stuff_count(void *arg);
void			do_eat(t_data *data);
void			do_die(t_data *data);
void			do_sleep(t_data *data);

// thread utils
int				create_semaphores(t_data *data);
int				open_sem_wrap(sem_t *sem, char *addr);
int				close_semaphores(t_data *data);
int				fork_processes(t_data *data);

// general utils
void			usleep_adj(t_data *data, unsigned long start_ms);
int				ft_atoi(const char *str);
int				log_error(char *str);
unsigned long	timestamp(unsigned long start_ms);
void			log_message(t_data *data, enum e_msg msg);

#endif