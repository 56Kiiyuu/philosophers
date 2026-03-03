/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:13:29 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/03 13:04:11 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	helper_check_finish_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (philo->data->nb_must_eat > 0
		&& philo->data->nb_finish >= philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		set_stop(philo->data);
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->eat / 2, philo->data);
	while (!simulation_stopped(philo->data))
	{
		if (philo->data->nb_philo == 1)
		{
			print_state(philo, "has taken a fork");
			precise_sleep(philo->data->die, philo->data);
			return (NULL);
		}
		eat(philo);
		if (simulation_stopped(philo->data))
			break ;
		sleeping(philo);
		if (simulation_stopped(philo->data))
			break ;
		thinking(philo);
		usleep(200);
		helper_check_finish_stop(philo);
	}
	return (NULL);
}
