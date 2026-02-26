/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevlim <kevlim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:38:54 by kevlim            #+#    #+#             */
/*   Updated: 2026/02/21 13:29:38 by kevlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				nb_must_eat;
	int				nb_finish;
	long int		start_time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	int				stop;
};

struct s_philo
{
	int				id;
	int				nb_eat;
	long int		last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
};

long int	timestamp(void);
void		precise_sleep(long time, t_data *data);

int			parse_args(int ac, char **av, t_data *data);
int			ft_atoi_safe(const char *str);
int			is_number(const char *str);

void		print_state(t_philo *philo, char *msg);

void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

int			simulation_stopped(t_data *data);
void		set_stop(t_data *data);

void		*monitor(void *arg);
void		*routine(void *arg);

int			init_data(t_data *data);
#endif
