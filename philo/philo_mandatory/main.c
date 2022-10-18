/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:35:04 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 16:59:27 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_baza *white_rabbit, int i)
{
	int		time;

	if (i == white_rabbit->filo_count)
		i = 0;
	pthread_mutex_lock(&white_rabbit->status[i]);
	time = what_current_time(*white_rabbit->t_start);
	if (time - white_rabbit->sages_arr[i]->current_life
		>= white_rabbit->how_long_life
		&& white_rabbit->sages_arr[i]->how_much_eat
		!= white_rabbit->how_much_need_eat)
	{
		pthread_mutex_lock(white_rabbit->mut_print);
		printf("time:%lld phil_num:%d died\n", what_current_time
			(*white_rabbit->t_start), white_rabbit->sages_arr[i]->id);
		return (0);
	}
	pthread_mutex_unlock(&white_rabbit->status[i]);
	i++;
	return (1);
}

int	main(int argc, char **argv)
{
	t_baza	*white_rabbit;
	int		i;

	white_rabbit = (t_baza *)malloc(sizeof(t_baza));
	if (!white_rabbit)
		error_exit (white_rabbit);
	white_rabbit->flag = 1;
	if (argc < 5 || argc > 6)
		return (start_error ("Incorrect number of arguments!", white_rabbit));
	if (checker (argc, argv, white_rabbit) == 1)
		parent_child_struct_init (argc, argv, white_rabbit);
	else
		return (start_error("Incorrect content of arguments!", white_rabbit));
	i = 0;
	pthread_mutex_lock (white_rabbit->monitor);
	while (white_rabbit->flag != 2)
	{
		pthread_mutex_unlock(white_rabbit->monitor);
		if (monitoring(white_rabbit, i) == 0)
			break ;
		pthread_mutex_lock(white_rabbit->monitor);
	}
	all_clean(white_rabbit);
	return (0);
}
