/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:07:59 by stalash           #+#    #+#             */
/*   Updated: 2024/10/28 21:32:18 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	print_case(t_philo *philo, int id, char *str)
{
	int	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->begaining;
	if (!dead_loop(philo))
		printf("%d %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	destory_all(t_program *pro, pthread_mutex_t *fork, char *str)
{
	int	i;

	i = -1;
	if (str)
		printf(RED"ERROR: Thread join doesn't work\n"RESET);
	pthread_mutex_destroy(&pro->write_lock);
	pthread_mutex_destroy(&pro->dead_lock);
	pthread_mutex_destroy(&pro->meal_lock);
	while (++i > pro->philos[0].nbr_philos)
	{
		pthread_mutex_destroy(&fork[i]);
	}
}
