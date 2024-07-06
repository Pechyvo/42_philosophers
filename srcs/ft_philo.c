/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:24:31 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/05 10:51:16 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	ft_state(t_philo *philo);
static int	ft_cycle(t_philo *philo);
static int	ft_manage_forks(t_philo *philo);
static int	ft_check_fork(t_philo *philo, int id, int id_next);

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		ft_logs(philo, COLOR_CYAN"is thinking");
		ft_usleep(1);
	}
	ft_state(philo);
	return (NULL);
}

static void	ft_state(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->log);
		if (ft_check_death(philo) == 1)
			break ;
		pthread_mutex_unlock(&philo->data->log);
		if (ft_cycle(philo))
			break ;
		pthread_mutex_lock(&philo->data->full_meal);
		if (philo->data->nb_meals && ++philo->meals == philo->data->nb_meals)
		{
			pthread_mutex_unlock(&philo->data->full_meal);
			break ;
		}
		pthread_mutex_unlock(&philo->data->full_meal);
	}
}

static int	ft_cycle(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
		ft_usleep(philo->data->t_die);
	if (ft_manage_forks(philo))
		return (1);
	ft_logs(philo, COLOR_BLUE"has taken a fork");
	ft_logs(philo, COLOR_GREEN"is eating");
	philo->last_meal = ft_get_time(philo->data->time);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->data->philo[philo->id].fork);
	pthread_mutex_unlock(&philo->data->philo[philo->id_next].fork);
	ft_logs(philo, COLOR_BLACK"is sleeping");
	ft_usleep(philo->data->t_sleep);
	ft_logs(philo, COLOR_CYAN"is thinking");
	return (0);
}

static int	ft_manage_forks(t_philo *philo)
{
	if (philo->id < philo->id_next)
		return (ft_check_fork(philo, philo->id, philo->id_next));
	return (ft_check_fork(philo, philo->id_next, philo->id));
}

static int	ft_check_fork(t_philo *philo, int id, int id_next)
{
	pthread_mutex_lock(&philo->data->philo[id].fork);
	ft_logs(philo, COLOR_BLUE"has taken a fork");
	if (ft_check_t_die(philo))
	{
		ft_logs(philo, COLOR_RED"died");
		pthread_mutex_unlock(&philo->data->philo[id].fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->philo[id_next].fork);
	return (0);
}

// ft_logs(philo, COLOR_BLUE"has taken a fork");
// ft_logs(philo, COLOR_GREEN"is eating");
// ft_logs(philo, COLOR_BLACK"is sleeping");
// ft_logs(philo, COLOR_CYAN"is thinking");
// ft_logs(philo, COLOR_RED"died");