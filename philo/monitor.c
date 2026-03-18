/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:19:14 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/18 14:48:00 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&philo->meal_mutex);
	now = timestamp();
	if (now - philo->last_meal >= philo->data->die)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_lock(&philo->data->stop_mutex);
		if (!philo->data->stop)
		{
			philo->data->stop = 1;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("%ld %d died\n", now - philo->data->start_time, philo->id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	helper_all_finished(t_data *data)
{
	int	finished;

	if (data->nb_must_eat <= 0)
		return (0);
	pthread_mutex_lock(&data->finish_mutex);
	finished = data->nb_finish;
	pthread_mutex_unlock(&data->finish_mutex);
	return (finished >= data->nb_philo);
}

int	helper_check_all_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (check_death(&data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (helper_all_finished(data))
		{
			set_stop(data);
			return (NULL);
		}
	}
	return (NULL);
}
