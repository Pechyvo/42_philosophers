/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:33:38 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/05 10:51:18 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	ft_logs(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->log);
	if (ft_check_death(philo) == 1)
		return ;
	if (ft_strcmp(msg, COLOR_RED"died") == 0)
		philo->data->dead = 1;
	printf(COLOR_PURPLE"%ld "COLOR_RESET COLOR_YELLOW"%d "COLOR_RESET
		"%s\n"COLOR_RESET, ft_get_time(philo->data->time), philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->log);
}

int	ft_error_output(char *msg)
{
	write(2, COLOR_RED"\n  ERROR » "COLOR_RESET, 22);
	write(2, COLOR_BLUE, ft_strlen(COLOR_BLUE));
	write(2, msg, ft_strlen(msg));
	write(2, "\n\n", 2);
	write(2, COLOR_RESET, ft_strlen(COLOR_RESET));
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	neg;

	i = 0;
	n = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n * neg);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
