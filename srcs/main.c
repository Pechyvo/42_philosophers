/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:19:29 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/05 02:20:05 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static int		ft_init_data(t_data *info, int argc, char **argv);
static int		ft_validate_data(t_data *data, int argc, char **argv);
static void		ft_init_philo(t_data *data);
static void		ft_destroy_mutex(t_data *data);

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error_output("Invalid number of arguments"));
	if (ft_init_data(&data, argc, argv))
		return (1);
	while (i < data.nb_philo)
	{
		pthread_create(&data.philo[i].thread, NULL, ft_philo, &data.philo[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&data.log);
	pthread_mutex_destroy(&data.full_meal);
	ft_destroy_mutex(&data);
	free(data.philo);
	return (0);
}

static int	ft_init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->nb_meals = 0;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	if (ft_validate_data(data, argc, argv))
		return (1);
	data->dead = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (ft_error_output("Malloc failed"));
	gettimeofday(&data->time, NULL);
	pthread_mutex_init(&data->log, NULL);
	pthread_mutex_init(&data->full_meal, NULL);
	ft_init_philo(data);
	return (0);
}

static int	ft_validate_data(t_data *data, int argc, char **argv)
{
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[2]) == 0
		|| ft_strlen(argv[3]) == 0 || ft_strlen(argv[4]) == 0)
		return (ft_error_output("Invalid arguments"));
	if (data->nb_philo < 1 || data->nb_philo > 200)
		return (ft_error_output("Invalid number of philos(min 1, max 200)"));
	if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60)
		return (ft_error_output("Invalid time(min 60ms)"));
	if (argc == 6 && data->nb_meals < 1)
		return (ft_error_output("Invalid number of meals(min 1)"));
	return (0);
}

static void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philo[i].fork, NULL);
		data->philo[i].id = i;
		data->philo[i].last_meal = ft_get_time(data->time);
		if (data->nb_philo == i + 1)
			data->philo[i].id_next = 0;
		else
			data->philo[i].id_next = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		i++;
	}
}

static void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork);
		i++;
	}
}
