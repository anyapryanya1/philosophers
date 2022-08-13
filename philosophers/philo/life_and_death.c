/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_and_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:05:18 by truthe            #+#    #+#             */
/*   Updated: 2022/04/30 16:59:23 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct t_kphilo
{
	int				id;
	long			start_time;
	long			*time_last_lunch;
	int				*count_lunch;
	pthread_mutex_t	*mut_left;
	pthread_mutex_t	*mut_right;
}					t_life;

void	sleep_think(t_life l, t_obj *w)
{
	pthread_mutex_lock(&w->print_mute);
	printf ("%ld %d %s\n", get_time() - l.start_time, l.id, "is sleeping");
	pthread_mutex_unlock(&w->print_mute);
	ft_ulseep(w->time_to_sleep);
	pthread_mutex_lock(&w->print_mute);
	printf ("%ld %d %s\n", get_time() - l.start_time, l.id, "is thinking");
	pthread_mutex_unlock(&w->print_mute);
}

void	life_death(t_life l, t_obj *w)
{
	while (1)
	{
		pthread_mutex_lock (l.mut_left);
		pthread_mutex_lock(&w->print_mute);
		printf ("%ld %d %s\n",
			get_time() - l.start_time, l.id, "has taken a fork");
		pthread_mutex_unlock(&w->print_mute);
		pthread_mutex_lock (l.mut_right);
		pthread_mutex_lock(&w->print_mute);
		printf ("%ld %d %s\n",
			get_time() - l.start_time, l.id, "has taken a fork");
		pthread_mutex_unlock(&w->print_mute);
		pthread_mutex_lock(&w->print_mute);
		printf ("%ld %d %s\n", get_time() - l.start_time, l.id, "is eating");
		pthread_mutex_unlock(&w->print_mute);
		*l.time_last_lunch = get_time();
		ft_ulseep(w->time_to_eat);
		pthread_mutex_unlock (l.mut_left);
		pthread_mutex_unlock (l.mut_right);
		l.count_lunch[0]--;
		if (l.count_lunch[0] == 0 && w->flag_arg == 1)
			return ;
		sleep_think (l, w);
	}
}

void	*my_philo(void *philo)
{
	t_obj	*w;
	t_life	l;

	w = (t_obj *)philo;
	pthread_mutex_lock(&w->print_mute);
	l.id = w->id;
	l.start_time = w->start_time;
	l.time_last_lunch = &w->p[w->id - 1].time_last_lunch;
	l.count_lunch = &w->p[w->id - 1].count_of_lunch;
	l.mut_left = &w->p[w->id - 1].mutex;
	if (l.id == 1)
		l.mut_right = &w->p[w->count - 1].mutex;
	else
		l.mut_right = &w->p[l.id - 2].mutex;
	*l.time_last_lunch = get_time();
	pthread_mutex_unlock(&w->print_mute);
	life_death (l, w);
	return (NULL);
}
