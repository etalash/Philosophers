/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:04:26 by stalash           #+#    #+#             */
/*   Updated: 2024/10/28 23:28:32 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_case(philo, philo->id, "has taken a fork (right)");
	if (philo->nbr_philos > 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_case(philo, philo->id, "has taken a fork (left)");
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->nbr_philos > 1)
		pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	time_for_eating(t_philo *philo)
{
	philo->eating = 1;
	print_case(philo, philo->id, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_eating = get_current_time();
	philo->eating_counter++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
}

void	time_for_thinking(t_philo *philo)
{
	print_case(philo, philo->id, "is thinking");
}

void	*table_process(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	if (philo->nbr_philos == 1)
	{
		print_case(philo, philo->id, "has taken a fork (right)");
		ft_usleep(philo->time_to_die + 1);
		return (pointer);
	}
	while (!(*philo->dead_flag))
	{
		take_forks(philo);
		time_for_eating(philo);
		release_forks(philo);
		print_case(philo, philo->id, "is sleeping");
		ft_usleep(philo->time_to_sleep);
		time_for_thinking(philo);
	}
	return (pointer);
}
