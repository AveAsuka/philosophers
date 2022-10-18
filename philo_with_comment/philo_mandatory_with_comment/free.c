#include "philo.h"

void free_mutex(t_baza  *the_end)
{
    int i;

    i = 0;
    while(i < the_end->filo_count) // когда ставлю <=, то всё идёт по пизде
    {   
        // printf("fork %d - %p\n", i, &the_end->status[i]); //del
        if (&the_end->status[i])
            pthread_mutex_destroy(&the_end->status[i]);
        else
            break;
        i++;
    }

    i = 0;
    while(i < the_end->filo_count) // когда ставлю <=, то всё идёт по пизде
    {   
        // printf("fork %d - %p\n", i, &the_end->mut[i]); //del
        if (&the_end->mut[i])
            pthread_mutex_destroy(&the_end->mut[i]);
        else
            break;
        i++;
    }
}

void all_clean(t_baza  *the_end)
{   
    int i;
    i = 0;
// Сначала чистим все мъютексы
    if (the_end->mut_print)
    {
        pthread_mutex_destroy(the_end->mut_print);
        free(the_end->mut_print);
    }
    if (the_end->monitor)
    {
        pthread_mutex_destroy(the_end->monitor);
        free(the_end->monitor);
    }
  
    free_mutex(the_end);

    if (the_end->status)
    {
        // pthread_mutex_destroy(the_end->status);
        free(the_end->status);
    }
    if (the_end->mut)
    {
        // pthread_mutex_destroy(the_end->mut);
        free(the_end->mut);
    }

// Потом чистим отдельного философа - как я понял отдельно поток и саму струтуру
    while(i < the_end->filo_count)
    {   
        // printf("%d sages - %p, %p\n", i, the_end->sages_arr[i]->thread, the_end->sages_arr[i]);
        if(the_end->sages_arr[i]->thread)
            free(the_end->sages_arr[i]->thread);
        if(the_end->sages_arr[i])
            free(the_end->sages_arr[i]);
        i++;
    }

// Потом всё остальное
    if (the_end->t_start)
        free(the_end->t_start);
    if (the_end->sages_arr)
        free(the_end->sages_arr); // не уверен, что правильно освобождаю двойнов массив
    if (the_end)
        free(the_end);
    return ;
}