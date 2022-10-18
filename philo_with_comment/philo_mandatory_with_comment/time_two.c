#include "philo.h"

long long int get_time()
{
    struct timeval  start;
    
    gettimeofday(&start, 0);
    // return (start.tv_sec * 1000 + start.tv_usec / 1000);
    return ((start.tv_sec * 1000000) + (start.tv_usec )); // перевод в микросекунды (10-6) обоих частей

}

long long int	what_current_time(struct timeval time)
{
	// return (get_time() - (time.tv_sec * 1000) - (time.tv_usec / 1000)); // перевод в миллисекунды (10-3) обоих частей
    // return (get_time() - (time.tv_sec * 1000000) - (time.tv_usec)); // перевод в микросекунды (10-6) обоих частей

    return ((time.tv_sec * 1000000) - (time.tv_usec)); // перевод в микросекунды (10-6) обоих частей
}

int main()
{
    struct timeval  t_start;

    // t_start = (struct timeval *)malloc(sizeof(struct timeval));
    gettimeofday(&t_start, NULL);
    printf("0 time:%lld\n", what_current_time(t_start));

    // printf("1 time:%lld\n", get_time());
    // usleep(1000);
    printf("2 time:%lld\n", what_current_time(t_start));
}