/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:38:24 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/19 15:16:03 by kevlim           ###   ########.fr       */
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
		if (timestamp() - start >= time)
			break ;
		if (time - (timestamp() - start) > 5)
			usleep(500);
		else
			usleep(50);
	}
}
