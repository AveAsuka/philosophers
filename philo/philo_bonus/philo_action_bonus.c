/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:50:00 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 21:34:42 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_go_to_eat(t_philo	*philo)
{
	sem_wait(philo->base->forks);
	sem_wait(philo->base->print);
	printf("time:%lld phil_num:%d has taken a fork\n",
		get_time() - philo->base->t_start, philo->id);
	sem_post(philo->base->print);
	sem_wait(philo->base->forks);
	sem_wait(philo->base->print);
	printf("time:%lld phil_num:%d has taken a fork\n",
		get_time() - philo->base->t_start, philo->id);
	sem_post(philo->base->print);
	sem_wait(philo->base->status[philo->status_id]);
	philo->current_life = get_time() - philo->base->t_start;
	sem_post(philo->base->status[philo->status_id]);
	sem_wait(philo->base->food[philo->status_id]);
	philo->how_much_eat++;
	sem_post(philo->base->food[philo->status_id]);
	sem_wait(philo->base->print);
	printf("time:%lld phil_num:%d is eating\n",
		get_time() - philo->base->t_start, philo->id);
	sem_post(philo->base->print);
	my_usleep(philo->base->how_long_eat);
	sem_post(philo->base->forks);
	sem_post(philo->base->forks);
}

void	philo_go_to_sleep(t_philo	*philo)
{
	sem_wait(philo->base->print);
	printf("time:%lld phil_num:%d is sleeping\n",
		get_time() - philo->base->t_start, philo->id);
	sem_post(philo->base->print);
	my_usleep(philo->base->how_long_sleep);
}

void	*monitor(void *data)
{
	t_philo	*philo_mon;

	philo_mon = (t_philo *)data;
	while (1)
	{
		usleep(200);
		sem_wait(philo_mon->base->status[philo_mon->status_id]);
		sem_wait(philo_mon->base->food[philo_mon->status_id]);
		if (philo_mon->flag == 0)
			exit(0);
		if (get_time() - philo_mon->base->t_start - philo_mon->current_life
			>= philo_mon->base->how_long_life)
		{
			sem_wait(philo_mon->base->print);
			printf("time:%lld phil_num:%d died\n",
				get_time() - philo_mon->base->t_start, philo_mon->id);
			sem_post(philo_mon->base->dead);
			exit(0);
		}
		sem_post(philo_mon->base->status[philo_mon->status_id]);
		sem_post(philo_mon->base->food[philo_mon->status_id]);
	}
}

void	philo_action_two(t_philo *philo)
{
	philo->flag = 0;
	sem_post(philo->base->food[philo->status_id]);
}

void	philo_action(t_baza *white_rabbit)
{
	t_philo		*philo;
	pthread_t	thread_mon;

	philo = white_rabbit->sages_arr;
	pthread_create(&thread_mon, NULL, monitor, philo);
	if (philo->id % 2 == 0)
		philo_go_to_sleep(philo);
	while (1)
	{
		philo_go_to_eat(philo);
		sem_wait(philo->base->food[philo->status_id]);
		if (philo->how_much_eat == philo->base->how_much_need_eat)
		{
			philo_action_two(philo);
			break ;
		}
		sem_post(philo->base->food[philo->status_id]);
		philo_go_to_sleep(philo);
		sem_wait(philo->base->print);
		printf("time:%lld phil_num:%d is thinking\n",
			get_time() - philo->base->t_start, philo->id);
		sem_post(philo->base->print);
	}
	my_usleep(philo->base->how_long_life);
	exit (0);
}
