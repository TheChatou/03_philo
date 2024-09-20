/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_03_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:45:25 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/20 17:30:35 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mtxs(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		safe_mutex(&data->philos[i].philo_mtx, DESTROY);
		safe_mutex(&data->forks[i].fork_mtx, DESTROY);
	}
	safe_mutex(&data->data_mtx, DESTROY);
	safe_mutex(&data->print_mtx, DESTROY);
	safe_mutex(&data->all_thr_ready_mtx, DESTROY);
}

void	join_threads(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (!data->philos[i].is_joined)
			safe_thread(&data->philos[i].thread_id, NULL, data, JOIN);
	}
}

bool	free_sim(t_data *data)
{
	if (data->start_threads)
	{
		join_threads(data);
		free_mtxs(data);
	}
	free(data->nb_philos_full);
	free(data->forks);
	free(data->philos);
	return (true);
}
