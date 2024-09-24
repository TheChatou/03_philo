/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02_classics.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 10:57:50 by fcoullou          #+#    #+#             */
/*   Updated: 2024/09/23 19:02:03 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_digit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

const char	*valid_input(const char *str)
{
	int			len;
	const char	*nb;

	len = 0;
	while (is_space((int)*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (ft_putstr_fd2("No negative number allowed", NULL), NULL);
	if (!is_digit(*str))
		return (ft_putstr_fd2("Invalid input", NULL), NULL);
	nb = str;
	while (is_digit(*str))
	{
		str++;
		len++;
	}
	if (len > 10)
		return (ft_putstr_fd2("Number too big", NULL), NULL);
	return (nb);
}

long	ft_atol(const char *str)
{
	long int	num;

	num = 0;
	str = valid_input(str);
	if (!str)
		return (-1);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		return (ft_putstr_fd2("Number too big", NULL), -1);
	return (num);
}

void	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while (*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
}
