#include "philo.h"

/* Моя ошибка была в том, что я вначале и инициализировал вилку и одновременно кидал
поток. А надо было вначале инициализировать все вилки, а потом уже кидать потоки! */
void mutex_init(t_baza *white_rabbit)
{
    int i;

    i = 0;
    while (i <= white_rabbit->filo_count - 1)
    {
        if(pthread_mutex_init (&white_rabbit->mut[i], NULL) != 0 ||
            pthread_mutex_init (&white_rabbit->status[i], NULL) != 0)
            error_exit(white_rabbit); // Если что-то пошло не так.
// printf("Вилка №%d, её адрес - %p\n", i+1, &white_rabbit->mut[i]); // было просто "i"
        i++;
    }
}

void mutex_filo_init(t_baza *white_rabbit, int i)
{ // Инициализируем вилки и вручаем мудрецу номера левых и правых вилок в массиве мъютексов
    if(i == 0) // левая "чужая"
        white_rabbit->sages_arr[i]->left = white_rabbit->filo_count - 1;
    else
        white_rabbit->sages_arr[i]->left = white_rabbit->sages_arr[i]->id - 2;
    if (white_rabbit->filo_count > 1)
        white_rabbit->sages_arr[i]->right = i; // правая "родная"
         
         
    printf("%d\n", white_rabbit->sages_arr[i]->left);
    printf("%d\n", white_rabbit->sages_arr[i]->right);
}

void id_base_filo_init(t_baza *white_rabbit)
{
    int i;
    i = 0;
    
// Малочим массив мудрецов
    white_rabbit->sages_arr = (t_philo **)malloc(sizeof(t_philo) * white_rabbit->filo_count); //[?] Возможно неккоректный маллок
    if (!white_rabbit->sages_arr)
       error_exit(white_rabbit);
// Заводим общее время
    white_rabbit->t_start = (struct timeval *)malloc(sizeof(struct timeval));
    gettimeofday(white_rabbit->t_start, NULL);

    while(i < white_rabbit->filo_count)
    {   // Маллочим структуру отдельного мудреца
        white_rabbit->sages_arr[i] = (t_philo *)malloc(sizeof(t_philo)); //[?] Возможно неккоректный маллок
        
        white_rabbit->sages_arr[i]->id = i + 1;
        white_rabbit->sages_arr[i]->status_id = i;

        white_rabbit->sages_arr[i]->current_life = 0;
        white_rabbit->sages_arr[i]->how_much_eat = 0;

        white_rabbit->sages_arr[i]->base = white_rabbit; // Кидаем подструктуре ссылку на основную
/* Разбираемся с вилками - сначал инициализировать все вилки, потом кидать потоки! */
        mutex_filo_init(white_rabbit, i);
        white_rabbit->sages_arr[i]->thread = (pthread_t	*)malloc(sizeof(pthread_t)); //[?] Возможно неккоректный маллок
        if (pthread_create(white_rabbit->sages_arr[i]->thread, NULL, &philo_threads,
				white_rabbit->sages_arr[i]) != 0 || pthread_detach(*white_rabbit->sages_arr[i]->thread) != 0
                || !white_rabbit->sages_arr[i] || !white_rabbit->sages_arr[i]->thread)
	            error_exit(white_rabbit);
        i++;
    }
}

void parent_child_struct_init(int argc, char **argv, t_baza *white_rabbit)
{
// Закидываем характеристики
    white_rabbit->flag = 1;
    white_rabbit->i = 1;
    white_rabbit->filo_count = fatoi(&*argv[1], white_rabbit);
    white_rabbit->how_long_life = fatoi(&*argv[2], white_rabbit);
    white_rabbit->how_long_eat = fatoi(&*argv[3], white_rabbit);
    white_rabbit->how_long_sleep = fatoi(&*argv[4], white_rabbit);
    if (argc == 6)
        white_rabbit->how_much_need_eat = fatoi(&*argv[5], white_rabbit);
    else
        white_rabbit->how_much_need_eat = -1;
// Делаем отдельный мутекст под принт, во избежании мещанины
    white_rabbit->mut_print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init (white_rabbit->mut_print, NULL);
// Делаем отдельный мутекст под монитор флага
    white_rabbit->monitor = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init (white_rabbit->monitor, NULL);
// Малочим массив статуса - для главного потока и каждого отдельного философа 
    white_rabbit->status = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * white_rabbit->filo_count);
// Малочим массив вилок
    white_rabbit->mut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * white_rabbit->filo_count);
// Инициализируем все мъютексы - и вилки, и статусы
    mutex_init(white_rabbit);
// Вручаем номера мудрецам, вилки, ссылку на родительскую структуру
    id_base_filo_init(white_rabbit);

    if(!white_rabbit->mut_print || !white_rabbit->t_start || !white_rabbit->status 
        || !white_rabbit->mut || !white_rabbit->monitor)
        error_exit(white_rabbit);

// Потом удалить
// printf("1 - %d, 2 - %d, 3 - %d, 4 - %d, 5 - %d.\n", white_rabbit->filo_count, white_rabbit->how_long_life, white_rabbit->how_long_eat, white_rabbit->how_long_sleep, white_rabbit->how_much_need_eat);
// printf("All ok!\n");
}