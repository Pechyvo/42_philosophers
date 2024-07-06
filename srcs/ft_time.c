/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:04:30 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/05 02:10:12 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

long	ft_get_time(struct timeval time)
{
	int				diff;
	struct timeval	now;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec * MILI + now.tv_usec / MILI)
		- (time.tv_sec * MILI + time.tv_usec / MILI);
	return (diff);
}

void	ft_usleep(int time)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (1)
	{
		if (ft_get_time(start) >= time)
			break ;
		usleep(100);
	}
}

int	ft_check_t_die(t_philo *philo)
{
	if (philo->data->t_die <= ft_get_time(philo->data->time) - philo->last_meal)
		return (1);
	return (0);
}

int	ft_check_death(t_philo *philo)
{
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->log);
		return (1);
	}
	return (0);
}
