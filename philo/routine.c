/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:13:29 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/11 15:46:56 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	helper_check_finish_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (philo->data->nb_must_eat > 0
		&& philo->data->nb_finish >= philo->data->nb_philo)
		set_stop(philo->data);
	pthread_mutex_unlock(&philo->data->finish_mutex);
}

void	check_must_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->nb_must_eat > 0
		&& philo->nb_eat >= philo->data->nb_must_eat)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		set_stop(philo->data);
	}
	else
		pthread_mutex_unlock(&philo->meal_mutex);
}

void	handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	precise_sleep(philo->data->die, philo->data);
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
			return (handle_one_philo(philo), NULL);
		check_must_eat(philo);
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
