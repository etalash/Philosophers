/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:33:14 by stalash           #+#    #+#             */
/*   Updated: 2024/10/28 23:30:44 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo, int time_to_die)
{
	int	time_since_last_meal;

	pthread_mutex_lock(philo->meal_lock);
	time_since_last_meal = get_current_time() - philo->last_eating;
	pthread_mutex_unlock(philo->meal_lock);
	if (time_since_last_meal >= time_to_die)
		return (1);
	return (0);
}

int	eatings_finished(t_philo *philo)
{
	int	eatings_counter;
	int	i;

	eatings_counter = 0;
	i = 0;
	if (philo->num_of_eating == -1)
		return (0);
	while (i < philo[0].nbr_philos)
	{
		pthread_mutex_lock(philo[0].meal_lock);
		if (philo[i].eating_counter >= philo[0].num_of_eating)
			eatings_counter++;
		pthread_mutex_unlock(philo[0].meal_lock);
		i++;
	}
	if (eatings_counter == philo[0].nbr_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead_flag = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

int	dead_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].nbr_philos)
	{
		if (philo_dead(&philo[i], philo[i].time_to_die))
		{
			print_case(&philo[i], philo[i].id, "died");
			pthread_mutex_lock(philo[i].dead_lock);
			*philo->dead_flag = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *pointer)
{
	t_philo	*thread;

	thread = (t_philo *)pointer;
	while (1)
	{
		if (eatings_finished(thread) == 1 || dead_check(thread) == 1)
			break ;
		ft_usleep(10);
	}
	return (pointer);
}
