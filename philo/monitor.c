/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:19:14 by kevlim            #+#    #+#             */
/*   Updated: 2026/02/26 12:33:12 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long	last_meal;

	if (simulation_stopped(philo->data))
		return (0);
	pthread_mutex_lock(&philo->data->death_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (timestamp() - last_meal > philo->data->die)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (!simulation_stopped(philo->data))
		{
			printf("%ldms %d died\n", timestamp() - philo->data->start_time,
				philo->id);
			set_stop(philo->data);
		}
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!simulation_stopped(data))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(&data->philos[i]))
			{
				return (NULL);
			}
			i++;
		}
		if (data->nb_must_eat > 0
			&& data->nb_finish >= data->nb_philo)
		{
			set_stop(data);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}
