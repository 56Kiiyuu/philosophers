/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:38:38 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/02 14:55:46 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = timestamp();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread_id,
				NULL, routine, &data->philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, monitor, data))
		return (1);
	return (0);
}

void	join_threads(t_data *data)
{
	int	i;

	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->finish_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
		return (1);
	if (start_threads(&data))
		return (1);
	join_threads(&data);
	cleanup(&data);
	return (0);
}
