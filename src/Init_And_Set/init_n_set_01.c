/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_set_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:25:35 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/20 13:57:05 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	Initialisation de t_data, puis parsing et check des inputs a l'intérieur
// de ft_atol. On malloc ensuite le nombre de philos et de fourchettes.
// 6e4 = 6000, soit 6 secondes. Si les inputs sont inferieurs a 6 secondes,
// on quitte le programme avec un message d'erreur.
bool	set_data(t_data *data, char **av)
{
	init_data(data);
	if (!set_data_args(data, av))
		return (false);
	if (!init_malloc_n_set_forks(data, data->nb_philo))
		return (false);
	if (!init_n_malloc_full_bools(data, data->nb_philo))
		return (false);
	if (!init_malloc_n_set_philos(data, data->nb_philo))
		return (false);
	if (!safe_mutex(&data->data_mtx, INIT)
		|| !safe_mutex(&data->all_thr_ready_mtx, INIT))
		return (false);
	return (true);
}

bool	set_data_args(t_data *data, char **av)
{
	if (!av[1] || !av[2] || !av[3] || !av[4])
		return (ft_putstr_fd2("Missing arguments", NULL), false);
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (data->nb_philo == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (false);
	if (av[5])
	{
		data->rounds = ft_atol(av[5]);
		if (data->rounds == -1)
			return (false);
		if (!data->rounds)
			return (ft_putstr_fd2("Rounds must be > 0", NULL), false);
	}
	else
		data->rounds = -1;
	return (true);
}

bool	init_malloc_n_set_philos(t_data *data, long max_philos)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * max_philos);
	if (!data->philos)
		return (ft_putstr_fd2("Malloc error", NULL), false);
	while (++i < max_philos)
	{
		init_philo(&data->philos[i]);
		if (!set_philos(data, &data->philos[i], i))
			return (false);
	}
	return (true);
}

bool	set_philos(t_data *data, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->data = data;
	if (!safe_mutex(&philo->philo_mtx, INIT))
		return (false);
	assign_forks(philo, &data->forks[0], philo->id - 1);
	return (true);
}

void	assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	philo->a_fork = &forks[(pos + 1) % philo->data->nb_philo];
	philo->b_fork = &forks[pos];
	if (philo->id % 2 == 1)
	{
		philo->a_fork = &forks[pos];
		philo->b_fork = &forks[(pos + 1) % philo->data->nb_philo];
	}
}
