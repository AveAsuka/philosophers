#include "philo.h"

/* Ошибки:
1. Раняя инициализация структуры времени;
2. Большие временные погрешности
3. Поздняя временная засечка в еде */

// 1) Получает нынешнее время в миллисекундах
long long int get_time()
{
    struct timeval  start;
    
    gettimeofday(&start, 0);
    return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

// gettimeofday - около 30%
// Погрешность usleep - 10%
// 2) Точное засыпание
void    my_usleep(int time_to_do)
{
    long long int time_start;
    long long int time_now;

    time_start = get_time();

    usleep(time_to_do * 900);

    time_now = get_time();

    while (time_now - time_start <= time_to_do)
    {
        time_now = get_time();
        usleep(50);
    }
}

// time.tv_sec -- в секундах
// time.tv_usec -- в микросекундах (10-6)
// 3) Запрос времени для терминала
long long int	what_current_time(struct timeval time)
{
	return (get_time() - (time.tv_sec * 1000) - (time.tv_usec / 1000)); // перевод в миллисекунды (10-3) обоих частей
    // return ((new.tv_sec * 1000000) + (new.tv_usec )); // перевод в микросекунды (10-6) обоих частей
}

