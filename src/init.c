/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:08:38 by stalash           #+#    #+#             */
/*   Updated: 2024/10/23 11:57:04 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexs(pthread_mutex_t *forks, int total_phios)
{
	int	i;

	i = -1;
	while (++i < total_phios)
		pthread_mutex_init(&forks[i], NULL);
}

void	lock_philos_process(t_philo *philo, t_program *program, \
									int i, pthread_mutex_t *fork)
{
	philo[i].write_lock = &program->write_lock;
	philo[i].dead_lock = &program->dead_lock;
	philo[i].meal_lock = &program->meal_lock;
	philo[i].l_fork = &fork[i];
	if (i == 0)
		philo[i].r_fork = &fork[philo[i].nbr_philos - 1];
	else
		philo[i].r_fork = &fork[i - 1];
}

void	init_philo(t_philo *philo, char **argv, \
		t_program *program, pthread_mutex_t *fork)
{
	int	i;

	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].dead_flag = &program->dead_flag;
		philo[i].eating = 0;
		philo[i].eating_counter = 0;
		philo[i].begaining = get_current_time();
		philo[i].last_eating = get_current_time();
		philo[i].nbr_philos = ft_atol(argv[1]);
		philo[i].time_to_die = ft_atol(argv[2]);
		philo[i].time_to_eat = ft_atol(argv[3]);
		philo[i].time_to_sleep = ft_atol(argv[4]);
		lock_philos_process(philo, program, i, fork);
		if (argv[5] != NULL)
			philo[i].num_of_eating = ft_atol(argv[5]);
		else
			philo[i].num_of_eating = -1;
	}
}

void	init_program(t_program *program, t_philo *philo)
{
	program->philos = philo;
	program->dead_flag = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
}

void	init_stuff(t_philo *philo, pthread_mutex_t *fork, \
					t_program *program, char **argv)
{
	init_program(program, philo);
	init_mutexs(fork, ft_atol(argv[1]));
	init_philo(philo, argv, program, fork);
}
