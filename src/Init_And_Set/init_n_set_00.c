/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_n_set_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:16:28 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/20 15:35:51 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_fork *fork)
{
	fork->id = 0;
	fork->fork_mtx = (t_mtx){0};
}

void	init_philo(t_philo *philo)
{
	philo->id = 0;
	philo->last_meal = 0;
	philo->nb_meal = 0;
	philo->is_full = false;
	philo->is_joined = false;
	philo->thread_id = (pthread_t){0};
	philo->a_fork = NULL;
	philo->b_fork = NULL;
	philo->philo_mtx = (t_mtx){0};
	philo->data = NULL;
}

void	init_data(t_data *data)
{
	data->nb_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->rounds = 0;
	data->start_sim = 0;
	data->start_threads = 0;
	data->nb_philos_full = NULL;
	data->end_sim = false;
	data->one_is_dead = false;
	data->all_threads_ready = false;
	data->philos = NULL;
	data->forks = NULL;
	data->data_mtx = (t_mtx){0};
	data->print_mtx = (t_mtx){0};
	data->all_thr_ready_mtx = (t_mtx){0};
}

bool	init_n_malloc_full_bools(t_data *data, int max_philos)
{
	data->nb_philos_full = malloc(sizeof(bool) * max_philos);
	if (!data->nb_philos_full)
		return (ft_putstr_fd2("Malloc error", NULL), false);
	memset(data->nb_philos_full, false, max_philos);
	return (true);
}

bool	init_malloc_n_set_forks(t_data *data, long max_philos)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(t_fork) * max_philos);
	if (!data->forks)
		return (ft_putstr_fd2("Malloc error", NULL), false);
	while (++i < max_philos)
	{
		init_fork(&data->forks[i]);
		if (!safe_mutex(&data->forks[i].fork_mtx, INIT))
			return (false);
		data->forks[i].id = i;
	}
	return (true);
}
