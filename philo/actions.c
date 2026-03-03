/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:53:00 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/03 13:03:33 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_state(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = timestamp();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_state(philo, "is eating");
	precise_sleep(philo->data->eat, philo->data);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->nb_eat++;
	if (philo->data->nb_must_eat > 0
		&& philo->nb_eat >= philo->data->nb_must_eat)
	{
		pthread_mutex_lock(&philo->data->finish_mutex);
		philo->data->nb_finish++;
		pthread_mutex_unlock(&philo->data->finish_mutex);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	release_forks(philo);
}

void	sleeping(t_philo *philo)
{
	print_state(philo, "is sleeping");
	precise_sleep(philo->data->sleep, philo->data);
}

void	thinking(t_philo *philo)
{
	print_state(philo, "is thinking");
}
