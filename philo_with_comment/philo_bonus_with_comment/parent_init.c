/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:35 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/14 21:34:23 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	id_base_filo_init(t_baza *white_rabbit, int i)
{
	white_rabbit->sages_arr->flag = 1;
	white_rabbit->sages_arr->id = i + 1;
	white_rabbit->sages_arr->status_id = i;
	white_rabbit->sages_arr->current_life = 0;
	white_rabbit->sages_arr->how_much_eat = 0;
	white_rabbit->sages_arr->base = white_rabbit;
// Вместо потока просто делаем функцию
	philo_action(white_rabbit);
// [!] Если не будет exit, то он начнёт клонить сам себя
	exit(0); // (или 1?) 
}

void semaphores(t_baza *white_rabbit)
{
	int	i;
	char *a;
	char *b;
	sem_unlink("forks");
	white_rabbit->forks = sem_open("forks", O_CREAT, 777, white_rabbit->filo_count);
	sem_unlink("print"); 
	white_rabbit->print = sem_open("print", O_CREAT, 777, 1);
	sem_unlink("dead"); 
	white_rabbit->dead = sem_open("dead", O_CREAT, 777, 1);
	sem_wait(white_rabbit->dead);
// Делаем два массива семафоров - статус и еда
	white_rabbit->food = (sem_t **)malloc(sizeof(sem_t) * white_rabbit->filo_count);
	white_rabbit->status = (sem_t **)malloc(sizeof(sem_t) * white_rabbit->filo_count);
	if (white_rabbit->forks <= 0 || white_rabbit->print <= 0 || white_rabbit->dead <= 0
		|| !white_rabbit->food || !white_rabbit->status)
		return(error_exit(white_rabbit));
	i = 0;
	while (i < white_rabbit->filo_count)
	{
		b = ft_itoa(i);
		a = ft_strjoin(ft_strjoin(b, "_"), b);

		sem_unlink(b);
		white_rabbit->food[i] = sem_open(b, O_CREAT, 777, 1);
		
		sem_unlink(a);
		white_rabbit->status[i] = sem_open(a, O_CREAT, 777, 1);
		
		if (!a || !b || white_rabbit->status[i] <= 0 || white_rabbit->food[i] <= 0)
			return(error_exit(white_rabbit));
		clean_char(a, b);
		i++;
	}
}

/* Сначала надо инициализировать все семафоры вместо мъютексов, потом
порождать форки */
void	parent_child_struct_init(int argc, char **argv, t_baza *white_rabbit)
{
	int	i;

	white_rabbit->flag = 1;
	white_rabbit->filo_count = fatoi(&*argv[1], white_rabbit);
	white_rabbit->how_long_life = fatoi(&*argv[2], white_rabbit);
	white_rabbit->how_long_eat = fatoi(&*argv[3], white_rabbit);
	white_rabbit->how_long_sleep = fatoi(&*argv[4], white_rabbit);
	if (argc == 6)
		white_rabbit->how_much_need_eat = fatoi(&*argv[5], white_rabbit);
	else
		white_rabbit->how_much_need_eat = -1;
// Открываем нужное количество семафоров
	semaphores(white_rabbit);
// Делаем массив pid-шников процессов	
	white_rabbit->pid = (int *)malloc(sizeof(int) * white_rabbit->filo_count);
	white_rabbit->sages_arr = (t_philo *)malloc(sizeof(t_philo));
	if (!white_rabbit->sages_arr || !white_rabbit->pid || white_rabbit->flag == 2)
		return(error_exit(white_rabbit));
// Время придется тут открывать
	white_rabbit->t_start = get_time();
	i = 0;
	while(i < white_rabbit->filo_count)
	{
		white_rabbit->pid[i] = fork();
		if (white_rabbit->pid[i] == -1)
		{
			error_exit(white_rabbit);
			break ;
		}
		if (white_rabbit->pid[i] == 0)
		{
			white_rabbit->sages_arr->t_meal = get_time();
			id_base_filo_init(white_rabbit, i);
		}
		i++;
	}
}
