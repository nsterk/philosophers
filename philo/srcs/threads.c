/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:35:28 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 15:39:29 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.>

void	*do_stuff(void *arg)
{
	t_thread	*thread;	
	t_data		*data;

	thread = (t_thread *)arg;
	data = (t_data *)thread->data;
	if (!thread->id % 2)
		usleep(1000);
	while (1)
	{
		if (!thread->times_eaten)
		{
			log_message(thread, get_timestamp(thread->start_ms), STATE_EAT);
			thread->times_eaten++;
			usleep(100000);
		}
		else
		{
			log_message(thread, get_timestamp(thread->start_ms), STATE_DEAD);
			break ;
		}
	}
	return (NULL);
}
