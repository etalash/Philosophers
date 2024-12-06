/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:35:47 by stalash           #+#    #+#             */
/*   Updated: 2024/10/28 23:21:53 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	algorithm(t_program *pro, pthread_mutex_t *fork)
{
	int			i;
	pthread_t	process;

	i = -1;
	if (pthread_create(&process, NULL, &monitoring, pro->philos) != 0)
		destory_all(pro, fork, "ERROR: Failed to create monitoring thread");
	while (++i < pro->philos->nbr_philos)
	{
		if (pthread_create(&pro->philos[i].thread, NULL, \
			&table_process, &pro->philos[i]) != 0)
			destory_all(pro, fork, "ERROR: Failed to create \
						philosopher thread");
	}
	if (pthread_join(process, NULL) != 0)
		destory_all(pro, fork, "ERROR: Thread join doesn't work");
	i = -1;
	while (++i < pro->philos[0].nbr_philos)
		if (pthread_join(pro->philos[i].thread, NULL) != 0)
			destory_all(pro, fork, "ERROR: Thread join doesn't work");
	return (0);
}
