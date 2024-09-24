/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:35:08 by chatou            #+#    #+#             */
/*   Updated: 2024/09/23 18:25:46 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!init_n_set_data(&data, av))
			return (free_sim(&data), 0);
		start_sim(&data);
		free_sim(&data);
	}
	else
		return (ft_putstr_fd2("Invalid number of arguments", NULL), 0);
}
