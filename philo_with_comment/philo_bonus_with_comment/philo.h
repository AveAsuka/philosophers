/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:43:46 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 20:50:00 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// leaks --atExit -- 

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h> // для времени

# include <sys/types.h> // для fork-ов
# include <semaphore.h> // библиотека для семафоров

# include <signal.h> // ?
# include <string.h>

typedef struct s_baza	t_baza;

typedef struct s_philo
{
	int					id;
	int					status_id;
	int					current_life;
	int					how_much_eat;
	t_baza				*base;
	int					flag;
	
	long long int		t_meal;
}					t_philo;

typedef struct s_baza
{
	int					flag;
	int					*pid;
	t_philo				*sages_arr;

	// struct timeval		*t_start;
	long long int		t_start;
//
	sem_t				*forks;
	sem_t				*print;

	sem_t				**status;
	sem_t				**food;
	
	sem_t				*dead;
//

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
					
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
					
// void			*philo_threads(void *data);
void			philo_action(t_baza *white_rabbit);

// Time
void			my_usleep(int time_to_do);
long long int	what_current_time(struct timeval time);
long long int	get_time(void);

// Errors
int				start_error(char *a, t_baza *white_rabbit);
void			error_exit(t_baza *white_rabbit);

// Free
void			all_clean(t_baza	*the_end);
void			clean_char(char *a, char *b);

// Bonus

#endif
