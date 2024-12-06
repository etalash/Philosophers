/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:14:19 by stalash           #+#    #+#             */
/*   Updated: 2024/10/23 11:54:06 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# define RED "\033[1;31m"
# define RESET "\033[0m"
# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nbr_philos;
	int				eating;
	int				eating_counter;
	int				num_of_eating;
	int				last_eating;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_die;
	int				begaining;
	int				*dead_flag;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}				t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

// ************** functions **************************

long	ft_atol(const char *s);
void	init_stuff(t_philo *philo, pthread_mutex_t *fork, \
				t_program *program, char **argv);
int		ft_usleep(size_t milliseconds);
int		get_current_time(void);
int		ft_usleep(size_t milliseconds);
void	print_case(t_philo *philo, int id, char *str);
int		algorithm(t_program *pro, pthread_mutex_t *fork);
void	*monitoring(void *pointer);
void	*table_process(void *pointer);
int		philo_dead(t_philo *philo, int time_to_die);
void	*table_process(void *pointer);
void	destory_all(t_program *pro, pthread_mutex_t *fork, char *str);
int		dead_loop(t_philo *philo);

#endif
