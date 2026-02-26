/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:13:29 by kevlim            #+#    #+#             */
/*   Updated: 2026/02/21 14:05:39 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_stopped(philo->data))
	{
		if (philo->data->nb_philo == 1)
		{
			print_state(philo, "has taken a fork");
			precise_sleep(philo->data->die, philo->data);
			return (NULL);
		}
		eat(philo);
		sleeping(philo);
		thinking(philo);
		if (philo->data->nb_must_eat > 0
			&& philo->data->nb_finish >= philo->data->nb_philo)
		{
			set_stop(philo->data);
			return (NULL);
		}
	}
	return (NULL);
}
