/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:54:19 by kevlim            #+#    #+#             */
/*   Updated: 2026/02/26 12:30:54 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_stopped(philo->data))
	{
		time = timestamp() - philo->data->start_time;
		printf("%ldms %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
