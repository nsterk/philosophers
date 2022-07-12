/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:04:00 by nsterk        #+#    #+#                 */
/*   Updated: 2022/07/12 13:59:22 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <types_bonus.h>
# include <stdio.h>
# include <stdlib.h>

bool			valid_args(t_data *data, char **argv, int argc);

// thread functions
void			do_stuff(t_data *data);
void			do_eat(t_data *data);
void			do_sleep(t_data *data);

// process functions

void			wait_for_children(t_data *data);

// thread utils
int				create_semaphores(t_data *data);
int				close_semaphores(t_data *data, bool unlink);
int				unlink_semaphores(void);
int				fork_processes(t_data *data);

void			init_child(t_data *data);

// general utils
	// string utils
size_t			ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
void			usleep_adj(unsigned long ms);
void			log_error(t_data *data, enum e_error err);
unsigned long	timestamp(unsigned long start_ms);
void			log_message(t_data *data, enum e_msg msg);

#endif