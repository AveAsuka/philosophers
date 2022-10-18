/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:35 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/08 15:54:46 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_baza *white_rabbit)
{
	int	i;

	i = 0;
	while (i <= white_rabbit->filo_count - 1)
	{
		if (pthread_mutex_init (&white_rabbit->mut[i], NULL) != 0
			|| pthread_mutex_init (&white_rabbit->status[i], NULL) != 0)
			error_exit(white_rabbit);
		i++;
	}
}

void	mutex_filo_init(t_baza *white_rabbit, int i)
{
	if (i == 0)
		white_rabbit->sages_arr[i]->left = white_rabbit->filo_count - 1;
	else
		white_rabbit->sages_arr[i]->left = white_rabbit->sages_arr[i]->id - 2;
	if (white_rabbit->filo_count > 1)
		white_rabbit->sages_arr[i]->right = i;
}

void	id_base_filo_init_two(t_baza *white_rabbit, int i)
{
	white_rabbit->sages_arr[i] = (t_philo *)malloc(sizeof(t_philo));
	white_rabbit->sages_arr[i]->id = i + 1;
	white_rabbit->sages_arr[i]->status_id = i;
	white_rabbit->sages_arr[i]->current_life = 0;
	white_rabbit->sages_arr[i]->how_much_eat = 0;
	white_rabbit->sages_arr[i]->base = white_rabbit;
}

void	id_base_filo_init(t_baza *white_rabbit)
{
	int	i;

	i = 0;
	white_rabbit->sages_arr = (t_philo **)malloc(sizeof(t_philo)
			* white_rabbit->filo_count);
	if (!white_rabbit->sages_arr)
		error_exit (white_rabbit);
	white_rabbit->t_start = (struct timeval *)malloc(sizeof(struct timeval));
	gettimeofday(white_rabbit->t_start, NULL);
	while (i < white_rabbit->filo_count)
	{
		id_base_filo_init_two(white_rabbit, i);
		mutex_filo_init(white_rabbit, i);
		white_rabbit->sages_arr[i]->thread = (pthread_t *)
			malloc(sizeof(pthread_t));
		if (pthread_create(white_rabbit->sages_arr[i]->thread, NULL,
				&philo_threads, white_rabbit->sages_arr[i]) != 0
			|| pthread_detach(*white_rabbit->sages_arr[i]->thread) != 0
			|| !white_rabbit->sages_arr[i]
			|| !white_rabbit->sages_arr[i]->thread)
			error_exit(white_rabbit);
		i++;
	}
}

void	parent_child_struct_init(int argc, char **argv, t_baza *white_rabbit)
{
	white_rabbit->flag = 1;
	white_rabbit->i = 1;
	white_rabbit->filo_count = fatoi(&*argv[1], white_rabbit);
	white_rabbit->how_long_life = fatoi(&*argv[2], white_rabbit);
	white_rabbit->how_long_eat = fatoi(&*argv[3], white_rabbit);
	white_rabbit->how_long_sleep = fatoi(&*argv[4], white_rabbit);
	if (argc == 6)
		white_rabbit->how_much_need_eat = fatoi(&*argv[5], white_rabbit);
	else
		white_rabbit->how_much_need_eat = -1;
	white_rabbit->mut_print = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init (white_rabbit->mut_print, NULL);
	white_rabbit->monitor = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init (white_rabbit->monitor, NULL);
	white_rabbit->status = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* white_rabbit->filo_count);
	white_rabbit->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* white_rabbit->filo_count);
	mutex_init(white_rabbit);
	id_base_filo_init(white_rabbit);
	if (!white_rabbit->mut_print || !white_rabbit->t_start
		|| !white_rabbit->status || !white_rabbit->mut
		|| !white_rabbit->monitor)
		error_exit(white_rabbit);
}
