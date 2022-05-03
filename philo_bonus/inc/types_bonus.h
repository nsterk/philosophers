/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/30 18:29:45 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/03 21:55:00 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

# include <stdbool.h>

enum e_msg
{
	e_fork,
	e_eat,
	e_sleep,
	e_think,
	e_die
};

typedef struct s_data
{
	unsigned long	start;
	int				nr_philos;
	int				current_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				to_eat;
	bool			death;
}				t_data;

#endif