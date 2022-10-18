#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>    // printf
# include <stdlib.h>   // malloc
# include <unistd.h>   // write
# include <pthread.h>  // для потоков
# include <string.h>   // [?] протестить без неё

# include <sys/time.h> // для struct timeval & gettimeofday

// leaks --atExit -- 

// struct timeval 
//     time_t      tv_sec;     секунды
//     suseconds_t tv_usec     микросекунды 

/* Важно зафиксировать разницу в единицах измерения: 
1) 10−3 с	миллисекунда	мс; 
2) 10−6 с	микросекунда	мкс.

1) в терминал надо в таких единицах выводить, и struct timeval в такое переводить;
2) usleep.

Погрешность работы программы нам дано около 10 мс, это важно учитывать! */

/* Язык С позволяет определять имена новых типов данных с помощью ключевого слова typedef. 
На самом деле здесь не создается новый тип данных, а определяется новое имя существующему типу. 
Он позволяет облегчить создание машинно-независимых программ. 
Единственное, что потребуется при переходе на другую платформу, - это изменить оператор typedef. 
Он также может помочь документировать код, позволяя назначать содержательные имена стандартным типам данных. 
Стандартный вид оператора typedef следующий:

typedef тип имя;

где тип — это любой существующий тип данных, а имя - это новое имя для данного типа. 
Новое имя определяется в дополнение к существующему имени типа, а не замещает его */
typedef pthread_mutex_t t_mutex; 
typedef struct s_baza	t_baza; // чтобы [ДОЧЕРНАЯ] могла ссылаться на [РОДИТЕЛЬСКУЮ]

// [ДОЧЕРНАЯ] Индувидуальная структура каждого потока
typedef struct s_philo
{
	pthread_t		*thread;
	int				id; 	   // личный номер философа
	int				status_id; // личный номер философа в массиве

	int				left;	// номер левой вилки в массиве мъютексов
	int				right;	// [подумать над тем, чтобы передавать ссылки на мьютексы]
	int				current_life; // фиксатор, когда поел, обновление цикла жизни

	int				how_much_eat; // если есть
	
	t_baza			*base;		  // ссылка на родительскую структуру
}					t_philo;

// [РОДИТЕЛЬСКАЯ] Техническая, "общая" структура для всех потоков
typedef struct s_baza
{
	int				flag; 
	int				i;
	t_philo		   	**sages_arr; // массив с структурами философов

	pthread_mutex_t	*mut; // массив всех вилок для каждого философа
	pthread_mutex_t	*status; // массив для проверки статуса философа главным потоком
	pthread_mutex_t	*mut_print; // ОБЩИЙ мъютекс на принтф
	pthread_mutex_t	*monitor; // общий мъютекс на флаг количества трапез

	struct timeval	*t_start;  // наш общий журнал времени

// Задаваемые параметры:
	int				filo_count;     // (1) сколько их всего
	int				how_long_life;  // (2)
	int				how_long_eat;   // (3)
	int				how_long_sleep; // (4)
	int				how_much_need_eat;   // (5)
}					t_baza;

// Checker
int		checker(int argc, char **argv, t_baza *white_rabbit);
int		fatoi(const char *str, t_baza *white_rabbit);

// Action
void		parent_child_struct_init(int argc, char **argv, t_baza *white_rabbit);
void		*philo_threads(void *data);

// Time
void			my_usleep(int time_to_do);
long long int	what_current_time(struct timeval time);

// Errors
int			start_error(char *a, t_baza *white_rabbit);
void		error_exit(t_baza *white_rabbit);

// Free
void	all_clean(t_baza  *the_end);

// Bonus

#endif
