/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:04:22 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/07 19:06:13 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(t_baza	*the_end)
{
	int	i;

	i = 0;
	while (i < the_end->filo_count)
	{
		if (&the_end->status[i])
			pthread_mutex_destroy(&the_end->status[i]);
		else
			break ;
		i++;
	}
	i = 0;
	while (i < the_end->filo_count)
	{
		if (&the_end->mut[i])
			pthread_mutex_destroy(&the_end->mut[i]);
		else
			break ;
		i++;
	}
}

void	all_clean_two(t_baza	*the_end)
{
	if (the_end->mut_print)
	{
		pthread_mutex_destroy(the_end->mut_print);
		free(the_end->mut_print);
	}
	if (the_end->monitor)
	{
		pthread_mutex_destroy(the_end->monitor);
		free(the_end->monitor);
	}
}

void	all_clean(t_baza	*the_end)
{
	int	i;

	i = 0;
	all_clean_two(the_end);
	free_mutex(the_end);
	if (the_end->status)
		free(the_end->status);
	if (the_end->mut)
		free(the_end->mut);
	while (i < the_end->filo_count)
	{
		if (the_end->sages_arr[i]->thread)
			free(the_end->sages_arr[i]->thread);
		if (the_end->sages_arr[i])
			free(the_end->sages_arr[i]);
		i++;
	}
	if (the_end->t_start)
		free(the_end->t_start);
	if (the_end->sages_arr)
		free(the_end->sages_arr);
	if (the_end)
		free(the_end);
	return ;
}
