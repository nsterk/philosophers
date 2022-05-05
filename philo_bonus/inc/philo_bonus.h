/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/05 19:02:38 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <types_bonus.h>
# include <stdio.h>

int				init_data(t_data *data, char **argv, int argc);

// thread functions
void			do_the_thing(t_data *data);
void			*do_stuff(void *arg);
void			*do_stuff_count(void *arg);

// thread utils
int				create_semaphores(t_data *data);
int				fork_processes(t_data *data);

// general utils
int				ft_atoi(const char *str);
int				log_error(char *str);
unsigned long	timestamp(unsigned long start_ms);

#endif