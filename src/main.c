/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chatou <chatou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:35:08 by chatou            #+#    #+#             */
/*   Updated: 2024/07/16 17:26:34 by chatou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h" 

int main(int ac, char **av)
{
    t_data data;
    
    if (ac == 5 || ac == 8)
    {
        parsing(&data, av);
        simulation(&data);
        clean_data(&data);
    }
    else
        return 0;
}

bool    basic_parsing(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9' || (ft_atol(av[i]) < INT_MAX && ft_atol(av[i]) > 0))
                return 0;
            j++;
        }
        i++;
    }
    return 1;
}

void    parsing(t_data *data, char **av)
{
    if (!basic_parsing(av))
        exit(EXIT_FAILURE);
    init_data(data);
    set_data(data, av);
}

void    init_data(t_data *data)
{
    data->nb_philo = 0;
    data->time_to_die = 0;
    data->time_to_eat = 0;
    data->time_to_sleep = 0;
    data->nb_must_eat = 0;
    data->start_time = 0;
    data->dead = 0;
    data->philo = NULL;
    data->fork = NULL;
    pthread_mutex_init(&data->print, NULL);
}


void    set_data(t_data *data, char **av)
{
    data->nb_philo = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]) * 1000;
    data->time_to_eat = ft_atoi(av[3]) * 1000;
    data->time_to_sleep = ft_atoi(av[4]) * 1000;
    if (av[5])
        data->nb_must_eat = ft_atoi(av[5]);
    else
        data->nb_must_eat = -1;
}
