/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   extra.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 20:59:03 by nsterk        #+#    #+#                 */
/*   Updated: 2022/05/03 21:15:04 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
This covers the edge case of there only being one philosopher, in which case it
will never be able to eat. I do not have a monitor that checks whether a philo
has died, so if I let the program run normally with one philosopher it will be
stuck waiting for a second fork that does not exist. 
*/

void	*one_philosopher(t_thread *thread, t_data *data)
{
	log_message(thread, e_fork);
	thread->resume = thread->timestamp + data->time_to_die;
	usleep_adj(thread, data->start);
	log_message(thread, e_die);
	return (NULL);
}
