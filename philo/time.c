/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:38:24 by kevlim            #+#    #+#             */
/*   Updated: 2026/02/21 13:41:39 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	timestamp(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	precise_sleep(long time, t_data *data)
{
	long	start;

	start = timestamp();
	while (!simulation_stopped(data))
	{
		if ((timestamp() - start) >= time)
			break ;
		usleep(50);
	}
}
