/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalchuk <svalchuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:19:28 by svalchuk          #+#    #+#             */
/*   Updated: 2024/07/05 02:09:08 by svalchuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define COLOR_RESET "\033[0m"
# define COLOR_BLACK "\033[1;30m"
# define COLOR_RED "\033[1;31m"
# define COLOR_GREEN "\033[1;32m"
# define COLOR_YELLOW "\033[1;33m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_PURPLE "\033[1;35m"
# define COLOR_CYAN "\033[1;36m"
# define COLOR_WHITE "\033[1;37m"

# define MILI 1000

typedef struct s_philo
{
	int				id;
	int				id_next;
	int				meals;
	int				last_meal;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nb_meals;
	int				dead;
	t_philo			*philo;
	struct timeval	time;
	pthread_mutex_t	log;
	pthread_mutex_t	full_meal;
}	t_data;

void	*ft_philo(void *arg);
void	ft_usleep(int time);
long	ft_get_time(struct timeval time);
int		ft_check_t_die(t_philo *philo);
int		ft_check_death(t_philo *philo);
void	ft_logs(t_philo *philo, char *msg);
int		ft_error_output(char *msg);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

#endif