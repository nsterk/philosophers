/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/06/15 23:19:39 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <types_bonus.h>
# include <stdio.h>
# include <stdlib.h>

bool			valid_args(t_data *data, char **argv, int argc);
int				init_data(t_data *data);

// thread functions
void			do_stuff(t_data *data);
void			do_eat(t_data *data);
void			do_sleep(t_data *data);

// process functions
void			kill_the_children(t_data *data);
void			wait_for_children(t_data *data);

// thread utils
int				create_semaphores(t_data *data);
int				open_semaphores(t_data *data);
int				close_semaphores(t_data *data, bool post, bool unlink);
int				unlink_semaphores(void);
int				fork_processes(t_data *data);

// general utils
void			usleep_adj(t_data *data, unsigned long ms);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
void			log_error(t_data *data, enum e_error err);
unsigned long	timestamp(unsigned long start_ms);
void			log_message(t_data *data, enum e_msg msg);
void			*monitor(void *arg);
char			*ft_strjoin(char const *s1, char const *s2);

#endif