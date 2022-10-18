/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:04:22 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 21:05:41 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_char(char *a, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

void	all_clean_two(t_baza	*white_rabbit)
{
	if (white_rabbit->pid)
		free(white_rabbit->pid);
	if (white_rabbit->sages_arr)
		free(white_rabbit->sages_arr);
	if (white_rabbit)
		free(white_rabbit);
}

void	all_clean(t_baza	*white_rabbit)
{
	int		i;
	char	*a;
	char	*b;

	sem_close(white_rabbit->forks);
	sem_close(white_rabbit->print);
	sem_close(white_rabbit->dead);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	i = 0;
	while (i < white_rabbit->filo_count)
	{
		sem_close(white_rabbit->food[i]);
		sem_close(white_rabbit->status[i]);
		b = ft_itoa(i);
		sem_unlink(b);
		a = ft_strjoin(ft_strjoin(b, "_"), b);
		sem_unlink(a);
		clean_char(a, b);
		i++;
	}
	all_clean_two(white_rabbit);
}
