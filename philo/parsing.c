/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 12:32:55 by kevlim            #+#    #+#             */
/*   Updated: 2026/03/02 13:20:55 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char	*str)
{
	int		i;
	long	res;

	res = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return ((int)res);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (!(argc == 5 || argc == 6))
		return (1);
	if (!is_numeric(argv[1]) || !is_numeric(argv[2])
		|| !is_numeric(argv[3]) || !is_numeric(argv[4]))
		return (1);
	data->nb_philo = ft_atoi(argv[1]);
	data->die = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nb_must_eat = ft_atoi(argv[5]);
	else
		data->nb_must_eat = -1;
	if (data->nb_philo <= 0 || data->die <= 0 || data->eat <= 0
		|| data->sleep <= 0)
		return (1);
	return (0);
}
