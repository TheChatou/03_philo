/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeada-si <jeada-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:21:48 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 13:00:52 by jeada-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sim_checker(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (is_starving(&data->philos[i]))
		{
			print_status(DIE, &data->philos[i], NO_DEBUG);
			set_bool_mtx(&data->data_mtx, &data->one_is_dead, true);
			return ;
		}
		if (is_all_philos_full(data->philos, data->nb_philo))
		{
			set_bool_mtx(&data->data_mtx, &data->end_sim, true);
			return ;
		}
		if (i == (data->nb_philo - 1))
			i = -1;
		usleep(1);
	}
	return ;
}

bool	is_all_philos_full(t_philo *philos, int max_philos)
{
	int		i;

	i = 0;
	while (i < max_philos)
	{
		if (!is_philo_full(&philos[i]))
			return (false);
		i++;
	}
	return (true);
}

void	monitor_sim(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		// if (is_philo_full(&data->philos[i]))
		// {
		// 	safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		// 	data->philos[i].is_joined = true;
		// }
		sim_checker(data);
		if (is_philo_dead(&data->philos[i]) || is_finished_sim(data))
			return ;
		if (i == (data->nb_philo - 1))
			i = -1;
		usleep(10);
	}
	return ;
}
