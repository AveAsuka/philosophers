#include "philo.h"

void philo_go_to_eat(t_philo	*philo)
{
    pthread_mutex_lock(&philo->base->mut[philo->left]);
    pthread_mutex_lock(philo->base->mut_print);
    printf("time:%lld phil_num:%d has taken a left fork - №%d, add: %p\n",
		what_current_time(*philo->base->t_start), philo->id, philo->left+1,
        &philo->base->mut[philo->left]);
    pthread_mutex_unlock(philo->base->mut_print);

    pthread_mutex_lock(&philo->base->mut[philo->right]);
    pthread_mutex_lock(philo->base->mut_print);
    printf("time:%lld phil_num:%d has taken a right fork - №%d, add: %p\n",
		what_current_time(*philo->base->t_start), philo->id, philo->right+1,
       &philo->base->mut[philo->right]);
    pthread_mutex_unlock(philo->base->mut_print);

// Я считаю, что счётик жизни должно обновляться в начале трапезы, а не в конце,
// трактовки тут разные
    pthread_mutex_lock(&philo->base->status[philo->status_id]);
    philo->current_life = what_current_time(*philo->base->t_start);
    philo->how_much_eat++; // Надо окружить мъютексом
    pthread_mutex_unlock(&philo->base->status[philo->status_id]);

    pthread_mutex_lock(philo->base->mut_print);
    printf("time:%lld phil_num:%d is eating\n",
		what_current_time(*philo->base->t_start), philo->id);
    pthread_mutex_unlock(philo->base->mut_print);

    my_usleep(philo->base->how_long_eat);

    pthread_mutex_unlock(&philo->base->mut[philo->left]);
    pthread_mutex_unlock(&philo->base->mut[philo->right]);
}

void philo_go_to_sleep(t_philo	*philo)
{
    pthread_mutex_lock(philo->base->mut_print);
    printf("time:%lld phil_num:%d is sleeping\n",
		what_current_time(*philo->base->t_start), philo->id);
    pthread_mutex_unlock(philo->base->mut_print);

    my_usleep(philo->base->how_long_sleep);
}

/* Четыре задачи стоят:
1. Разобраться с едой;
2. Разобраться со сном;
3. Разобраться со смертью;
4. Разобраться с временем.

Проблемы: 
флагов; +
одного философа - одной вилки - смерти; + 
как считать сколько подумал; +
взаимозапирания на 1000; +
два фило берут одну вилку, когда она уже взята; +
связь с main-ом, чтобы цикл заканчивался +
выход остальных потоков, когда первый фило умирает + */
void	*philo_threads(void *data)
{
    t_philo	*philo;
    philo = (t_philo *)data;
    
// pthread_mutex_lock(philo->base->mut_print);
// printf("Фило_%d в фило_треде. current_life = %d\n", philo->id, philo->current_life);
// pthread_mutex_unlock(philo->base->mut_print);

    if (philo->id % 2 == 0) // Если у фило чётный номер, то он идёт спать
        philo_go_to_sleep(philo);

/* Тут не нужен break, когда фило умирает, достаточно проверять сколько осталось жить
и когда умирает, после чего меняем флаг, из-за чего остальные фило выйдут из цикла
сами по себе */
    while(1)
    {
        philo_go_to_eat(philo);

        pthread_mutex_lock(&philo->base->status[philo->status_id]);
        if (philo->how_much_eat == philo->base->how_much_need_eat)
        {
            pthread_mutex_unlock(&philo->base->status[philo->status_id]);            
            break;
        }
        pthread_mutex_unlock(&philo->base->status[philo->status_id]);

        philo_go_to_sleep(philo);

        pthread_mutex_lock(philo->base->mut_print);
        printf("time:%lld phil_num:%d is thinking\n", what_current_time(*philo->base->t_start), philo->id);
        pthread_mutex_unlock(philo->base->mut_print);
    }

    pthread_mutex_lock(philo->base->mut_print);
    if (philo->base->i < philo->base->filo_count)
        philo->base->i = philo->base->i + 1;
    else
    {
        pthread_mutex_lock(philo->base->monitor);
        philo->base->flag = 2;
        pthread_mutex_unlock(philo->base->monitor);
    }
    pthread_mutex_unlock(philo->base->mut_print);

    return (NULL);
}
