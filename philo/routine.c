/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:13:29 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/18 15:21:01 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_meal_status(t_philo *philo)
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
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (philo->data->nb_must_eat > 0
		&& philo->data->nb_finish >= philo->data->nb_philo)
		set_stop(philo->data);
	pthread_mutex_unlock(&philo->data->finish_mutex);
}

void	handle_one_philo(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	precise_sleep(philo->data->die, philo->data);
}

void	thinking_dynamic(t_philo *philo)
{
	long	t_think;

	if (philo->data->nb_philo % 2 == 0)
		return ;
	t_think = (philo->data->eat * 2) - philo->data->sleep;
	if (t_think < 0)
		t_think = 0;
	if (philo->data->die >= (philo->data->eat * 3))
	{
		precise_sleep(t_think * 0.2, philo->data);
	}
}

void	initial_delay(t_philo *philo)
{
	if (philo->data->nb_philo == 3)
	{
		if (philo->id == 2)
			precise_sleep(philo->data->eat, philo->data);
		else if (philo->id == 3)
			precise_sleep(philo->data->eat + 80, philo->data);
	}
	else if (philo->data->nb_philo % 2 != 0)
	{
		if (philo->id % 2 == 0)
			precise_sleep(philo->data->eat / 2, philo->data);
	}
	else if (philo->id % 2 == 0)
		precise_sleep(philo->data->eat / 2, philo->data);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_delay(philo);
	while (!simulation_stopped(philo->data))
	{
		if (philo->data->nb_philo == 1)
			return (handle_one_philo(philo), NULL);
		check_meal_status(philo);
		eat(philo);
		if (simulation_stopped(philo->data))
			break ;
		sleeping(philo);
		if (simulation_stopped(philo->data))
			break ;
		thinking(philo);
		thinking_dynamic(philo);
	}
	return (NULL);
}
