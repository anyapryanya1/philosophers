/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_and_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:25:01 by truthe            #+#    #+#             */
/*   Updated: 2022/04/30 17:28:59 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	life_death2(t_obj *w)
{
	if (w->count_of_lunch == 0 && w->flag_arg == 1)
		exit(0);
	sem_wait(w->print_sem);
	printf ("%ld %d %s\n", get_time() - w->start_time, w->id, "is sleeping");
	sem_post(w->print_sem);
	ft_ulseep(w->time_to_sleep);
	sem_wait(w->print_sem);
	printf ("%ld %d %s\n", get_time() - w->start_time, w->id, "is thinking");
	sem_post(w->print_sem);
}

void	life_death(t_obj *w)
{
	while (1)
	{
		sem_wait(w->sem_fork);
		sem_wait(w->print_sem);
		printf("%ld %d %s\n",
			get_time() - w->start_time, w->id, "has taken a fork");
		sem_post(w->print_sem);
		sem_wait(w->sem_fork);
		sem_wait(w->print_sem);
		printf ("%ld %d %s\n",
			get_time() - w->start_time, w->id, "has taken a fork");
		sem_post(w->print_sem);
		sem_wait(w->print_sem);
		printf ("%ld %d %s\n",
			get_time() - w->start_time, w->id, "is eating");
		sem_post(w->print_sem);
		w->time_last_lunch = get_time();
		ft_ulseep(w->time_to_eat);
		sem_post(w->sem_fork);
		sem_post(w->sem_fork);
		w->count_of_lunch--;
		life_death2 (w);
	}
}

void	*check_death(void *tmp)
{
	t_obj	*w;

	w = (t_obj *) tmp;
	sem_wait(w->death);
	sem_post(w->death);
	exit(1);
}

void	*my_philo(t_obj *w, int id)
{
	pthread_t	death;

	w->id = id;
	w->time_last_lunch = get_time();
	pthread_create(&w->thread, NULL, ft_check_dead, w);
	usleep(50);
	pthread_create(&death, NULL, check_death, w);
	life_death (w);
	return (NULL);
}
