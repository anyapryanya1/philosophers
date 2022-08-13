/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truthe <truthe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:09:56 by truthe            #+#    #+#             */
/*   Updated: 2022/04/30 18:13:51 by truthe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork(t_obj *w)
{
	int		i;
	pid_t	*pid;
	sem_t	*er;

	er = NULL;
	i = 0;
	pid = (pid_t *) malloc(sizeof(pid_t) * (w->count + 1));
	while (i < w->count)
	{
		pid[i] = fork();
		if (pid[i] != 0)
		{
			w->id = i + 1;
			w->sem_fork = er;
			my_philo(w, i + 1);
		}
		i++;
	}
}

int	init_philo(t_obj *w, int ac, char **argv)
{
	int		i;
	sem_t	*er;

	i = 0;
	if (ac == 6)
		w->flag_arg = 1;
	else
		w->flag_arg = 0;
	w->count = ft_atoi(argv[1]);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/death");
	w->death = sem_open("/death", O_CREAT, 0644, 0);
	er = sem_open("/forks", O_CREAT, 0644, w->count);
	w->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	w->time_to_die = ft_atoi(argv[2]);
	w->time_to_eat = ft_atoi(argv[3]);
	w->time_to_sleep = ft_atoi(argv[4]);
	if (w->flag_arg == 1)
			w->count_of_lunch = ft_atoi(argv[5]);
	ft_fork(w);
	return (0);
}

void	*ft_check_dead(void *phil)
{
	t_obj	*w;

	w = (t_obj *)phil;
	while (1)
	{
		if (get_time() - w->time_last_lunch > w->time_to_die)
		{
			sem_wait (w->print_sem);
			printf ("%ld %d died\n", get_time() - w->start_time, w->id);
			sem_post(w->death);
			exit (1);
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_obj	w;
	int		i;

	i = 0;
	w.start_time = get_time();
	if ((argc != 5 && argc != 6) || ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60 || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (write(1, "error\n", 6));
	if (init_philo(&w, argc, argv) == 1)
		return (1);
	return (0);
}
