/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:43:46 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 17:44:08 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_baza	t_baza;

typedef struct s_philo
{
	pthread_t			*thread;
	int					id;
	int					status_id;
	int					left;
	int					right;
	int					current_life;
	int					how_much_eat;
	t_baza				*base;
}					t_philo;

typedef struct s_baza
{
	int					flag;
	int					i;
	t_philo				**sages_arr;
	pthread_mutex_t		*mut;
	pthread_mutex_t		*status;
	pthread_mutex_t		*mut_print;
	pthread_mutex_t		*monitor;
	struct timeval		*t_start;
	int					filo_count;
	int					how_long_life;
	int					how_long_eat;
	int					how_long_sleep;
	int					how_much_need_eat;
}					t_baza;

// Checker
int				checker(int argc, char **argv, t_baza *white_rabbit);
int				fatoi(const char *str, t_baza *white_rabbit);

// Action
void			parent_child_struct_init(int argc, char **argv,
					t_baza *white_rabbit);
void			*philo_threads(void *data);

// Time
void			my_usleep(int time_to_do);
long long int	what_current_time(struct timeval time);

// Errors
int				start_error(char *a, t_baza *white_rabbit);
void			error_exit(t_baza *white_rabbit);

// Free
void			all_clean(t_baza	*the_end);

#endif
