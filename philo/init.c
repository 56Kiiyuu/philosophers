/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:47:47 by kevlim            #+#    #+#             */
/*   Updated: 2026/02/21 13:37:23 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].data = data;
		data->philos[i].l_fork = &data->forks[i];
		data->philos[i].r_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}

int	init_data(t_data *data)
{
	data->stop = 0;
	data->nb_finish = 0;
	data->start_time = timestamp();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	if (init_mutexes(data))
		return (1);
	init_philos(data);
	return (0);
}
