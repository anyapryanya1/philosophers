/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:31:33 by truthe            #+#    #+#             */
/*   Updated: 2022/04/30 18:37:38 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_obj *w, int ac, char **argv)
{
	int	i;

	i = 0;
	if (ac == 6)
		w->flag_arg = 1;
	else
		w->flag_arg = 0;
	w->count = ft_atoi(argv[1]);
	w->p = (t_philo *) malloc(sizeof(t_philo) * (w->count + 1));
	if (!w->p)
		return (1);
	w->time_to_die = ft_atoi(argv[2]);
	w->time_to_eat = ft_atoi(argv[3]);
	w->time_to_sleep = ft_atoi(argv[4]);
	while (i < w->count)
	{
		if (pthread_mutex_init(&w->p[i].mutex, NULL) != 0)
			return (1);
		if (w->flag_arg == 1)
			w->p[i].count_of_lunch = ft_atoi(argv[5]);
		i++;
	}
	return (0);
}

void	*check_death(void *phil)
{
	int		i;
	t_obj	*w;
	int		count_lunch;

	w = (t_obj *)phil;
	count_lunch = 1;
	while (1)
	{
		i = -1;
		while (++i < w->count)
		{
			if (w->p[i].count_of_lunch == 0 && w->flag_arg == 1)
				count_lunch++;
			if (get_time() - w->p[i].time_last_lunch > w->time_to_die)
			{
				w->flag_to_die = 1;
				pthread_mutex_lock(&w->print_mute);
				printf ("%ld %d died\n", get_time() - w->start_time, i + 1);
				return (NULL);
			}
		}
		if (count_lunch >= w->count)
			return (NULL);
	}
	return (NULL);
}

void	create_pthreade(t_obj *w)
{
	pthread_t	*t;
	int			i;

	t = (pthread_t *) malloc (sizeof(pthread_t) * (w->count + 2));
	pthread_mutex_init(&w->print_mute, NULL);
	i = 0;
	while (i < w->count)
	{
		if (i % 2 == 0)
		{
			w->id = i + 1;
			pthread_create(&t[i], NULL, my_philo, w);
			usleep (50);
		}
		i++;
	}
	create_pthreade2(w);
}

void	create_pthreade2(t_obj *w)
{
	int			i;
	pthread_t	*t;

	i = 0;
	t = (pthread_t *) malloc (sizeof(pthread_t) * (w->count + 2));
	while (i < w->count)
	{
		if (i % 2 != 0)
		{
			w->id = i + 1;
			pthread_create(&t[i], NULL, my_philo, w);
			usleep (50);
		}
		i++;
	}
	check_death(w);
	return ;
}

int	main(int argc, char **argv)
{
	t_obj	w;

	w.start_time = get_time();
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60
		|| (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (write(1, "error\n", 6));
	if (init_philo(&w, argc, argv) == 1)
		return (1);
	create_pthreade(&w);
	return (0);
}
