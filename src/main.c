/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stalash <stalash@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:13:42 by stalash           #+#    #+#             */
/*   Updated: 2024/10/23 11:45:27 by stalash          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_number(const char *str)
{
	if (*str == '\0')
		return (0);
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			printf(RED"ERROR: Arguments should be Numbers\n"RESET);
			return (0);
		}
		str++;
	}
	return (1);
}

long	ft_atol(const char *s)
{
	int		x;
	int		sign;
	long	out;

	x = 0;
	sign = 1;
	out = 0;
	if (!s)
		return (0);
	while (s[x] && (s[x] == ' ' || (s[x] >= 9 && s[x] <= 13)))
		x++;
	if (s[x] == '-')
	{
		sign = -1 * sign;
		x++;
	}
	else if (s[x] == '+')
		x++;
	while (s[x] && (s[x] >= '0' && s[x] <= '9'))
	{
		out = out * 10 + s[x] - '0';
		x++;
	}
	return (out * sign);
}

int	parsing(char **argv, int argc)
{
	int		i;
	long	check_int_max;

	i = 0;
	while (++i < argc)
	{
		check_int_max = ft_atol(argv[1]);
		if (check_int_max > PHILO_MAX || check_int_max <= 0)
		{
			printf(RED"ERROR: Invalid number of Philosophers"RESET);
			return (1);
		}
		if (!ft_is_number(argv[i]))
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	mutex[PHILO_MAX];
	t_philo			philo[PHILO_MAX];
	t_program		program;

	if (argc == 6 || argc == 5)
	{
		if (parsing(argv, argc) == 1)
			return (0);
		init_stuff(philo, mutex, &program, argv);
		algorithm(&program, mutex);
	}
	else
		printf(RED"ERROR: Not enough Arguments\n"RESET);
	return (0);
}
