/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:50:00 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 17:45:21 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_go_to_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->base->mut[philo->left]);
	pthread_mutex_lock(philo->base->mut_print);
	printf("time:%lld phil_num:%d has taken a fork\n",
		what_current_time(*philo->base->t_start), philo->id);
	pthread_mutex_unlock(philo->base->mut_print);
	pthread_mutex_lock(&philo->base->mut[philo->right]);
	pthread_mutex_lock(philo->base->mut_print);
	printf("time:%lld phil_num:%d has taken a fork\n",
		what_current_time(*philo->base->t_start), philo->id);
	pthread_mutex_unlock(philo->base->mut_print);
	pthread_mutex_lock(&philo->base->status[philo->status_id]);
	philo->current_life = what_current_time(*philo->base->t_start);
	philo->how_much_eat++;
	pthread_mutex_unlock(&philo->base->status[philo->status_id]);
	pthread_mutex_lock(philo->base->mut_print);
	printf("time:%lld phil_num:%d is eating\n",
		what_current_time(*philo->base->t_start), philo->id);
	pthread_mutex_unlock(philo->base->mut_print);
	my_usleep(philo->base->how_long_eat);
	pthread_mutex_unlock(&philo->base->mut[philo->left]);
	pthread_mutex_unlock(&philo->base->mut[philo->right]);
}

void	philo_go_to_sleep(t_philo	*philo)
{
	pthread_mutex_lock(philo->base->mut_print);
	printf("time:%lld phil_num:%d is sleeping\n",
		what_current_time(*philo->base->t_start), philo->id);
	pthread_mutex_unlock(philo->base->mut_print);
	my_usleep(philo->base->how_long_sleep);
}

void	philo_threads_two(t_philo	*philo)
{
	if (philo->base->i < philo->base->filo_count)
		philo->base->i = philo->base->i + 1;
	else
	{
		pthread_mutex_lock(philo->base->monitor);
		philo->base->flag = 2;
		pthread_mutex_unlock(philo->base->monitor);
	}
}

void	*philo_threads(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		philo_go_to_sleep(philo);
	while (1)
	{
		philo_go_to_eat(philo);
		pthread_mutex_lock(&philo->base->status[philo->status_id]);
		if (philo->how_much_eat == philo->base->how_much_need_eat)
		{
			pthread_mutex_unlock(&philo->base->status[philo->status_id]);
			break ;
		}
		pthread_mutex_unlock(&philo->base->status[philo->status_id]);
		philo_go_to_sleep(philo);
		pthread_mutex_lock(philo->base->mut_print);
		printf("time:%lld phil_num:%d is thinking\n",
			what_current_time(*philo->base->t_start), philo->id);
		pthread_mutex_unlock(philo->base->mut_print);
	}
	pthread_mutex_lock(philo->base->mut_print);
	philo_threads_two(philo);
	pthread_mutex_unlock(philo->base->mut_print);
	return (NULL);
}
