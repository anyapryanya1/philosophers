/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:30:43 by truthe            #+#    #+#             */
/*   Updated: 2022/04/30 18:10:39 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct k_obj
{
	int			count;
	int			flag_arg;
	int			flag_to_die;
	long		start_time;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			id;
	long		time_last_lunch;
	int			count_of_lunch;
	sem_t		*sem_fork;
	pid_t		*pid;
	pthread_t	thread;
	sem_t		*print_sem;
	sem_t		*death;
}				t_obj;

void	ft_ulseep(int n);
long	get_time(void);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *c);
void	*my_philo(t_obj *w, int id);
void	*ft_check_dead(void *phil);

#endif