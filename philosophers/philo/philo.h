/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:00:26 by truthe            #+#    #+#             */
/*   Updated: 2022/04/30 17:06:55 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct k_philo
{
	long			time_last_lunch;
	int				count_of_lunch;
	pthread_mutex_t	mutex;
}					t_philo;

typedef struct k_obj
{
	int				count;
	int				flag_arg;
	int				flag_to_die;
	long			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				id;
	pthread_mutex_t	print_mute;
	t_philo			*p;
}					t_obj;

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *c);
long	get_time(void);
void	ft_ulseep(int n);
void	*check_death(void *phil);
void	*my_philo(void *philo);
void	create_pthread(t_obj w);
void	create_pthreade2(t_obj *w);
#endif