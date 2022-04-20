#include <philo.h>
#include <stdio.h>

void	print_info(t_data *data)
{
	printf("nr_philos: %d\ntime_to_die: %d\ntime_to_eat: %d\ntime_to_sleep:%d\nto_eat: %d\n", data->nr_philos, 
	data->time_to_die, data->time_to_eat, data->time_to_sleep, data->to_eat);
	printf("data->start_ms: %lld\n", data->start_ms);
	usleep(data->time_to_sleep * 1000);
	printf("ms elapsed since sleep: %lld\n", get_timestamp(data->start_ms));
	return ;
}