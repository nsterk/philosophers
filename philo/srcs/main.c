/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 13:58:35 by nsterk        #+#    #+#                 */
/*   Updated: 2022/04/20 18:21:35 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect nr of arguments provided\n");
		return (0);
	}
	if (init_data(&data, argv, argc))
	{
		printf("woopsie poopsie in init_data\n");
		return (0);
	}
	spawn_threads(&data);
	return (0);
}
