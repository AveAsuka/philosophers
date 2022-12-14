#include "philo.h"

/* ВОПРОС: 1 поток на себя всё оттягивает, в пост-последнюю лишнюю итерацию 
почему-то заходит второй поток
ОТВЕТ: Мъютексы очень быстрые! Надо их искусственно затормаживать!
Иначе второй поток не успевает поучаствовать в работе цикла.
Даже с замедлением потоки могут залететь в цикл неравномерно, один может всё на себя перетянуть -
косвенно это связано с погрешностью usleep-а, а так-же с погрешностью pthread_create.
//
Можно использовать технические usleep для нормального взаимодействия -
НЕТ, нужно нечётных или чётных фило отправлять в сон вместо этого!
//
Надо разобраться с нумерацией вилок - можно двумя способами, как я понял - через массив,
как пока у меня, и через передачу номера указателю конкретного философа
//
Чем больше потоков, тем больше они времени отрабатывают, так как позже выходят из цикла
//
24.06. надо подумать над новым уровнем сложности - что делать дальше?
Арина предлагает делать проект (неожиданно), ввести time_to_eat и time_to_die.
Ещё подумать над зацикливанием подачи философов и параметров. */

/* С чего начать?
Наверно надо размножить философов, и промоделировать у них наличие рядом
вилок.
Насчет вилок наверно дать им индивидуальный номер, как и философам.

Три глобальные задачи:
I. Размножить философов;
II. Моделировать их жизненный цикл;
III. Контроль их доступа к единому ресурсу - вилки.

Если так размышлять, то может просимулировать двоих философов и одну вилку для начала?
Ну то есть в вечном цикле это дело сидит и принтфит вилка выражена printf и окружена мьютексом
надо подкрутить таймер - типо каждый философ держит вилку по 10 мкс (пока обойдемся простым usleep) */

/* main по сути тоже почему-то поток, который приоритетнее
других потоков - это надо уточнить */

/* То есть сюжет такой:
1) Чекер; (+)
2.1) Инициализация родительской структуры и ...; (+)
2.2) ... дочерних струтур (+)
3) Цикл подачи потоков... ;
4) ... в общую для них "void - void" функцию, в которой... ;
5) вечный цикл (до смерти первого философа), с кучей подфункций (еда, сон, прочее);
6) Ко всему этому прочее: чекер жизни фило (в начале и в конце сна и еды), 
free-функции, time-функции (уже есть), error-функции (они под вопросом);
!) Возможно что-то упустил - допишу. */
int main(int argc, char **argv)
{
    t_baza  *white_rabbit; // общая структура
    int i;
// Маллочим родительскую структуру - после этого сбрасываются все характеристики!
    white_rabbit = (t_baza *)malloc(sizeof(t_baza));
    if (!white_rabbit)
       error_exit(white_rabbit);
    white_rabbit->flag = 1;
    if (argc < 5 || argc > 6)
        return (start_error("Incorrect number of arguments!", white_rabbit));
    if (checker(argc, argv, white_rabbit) == 1)
        parent_child_struct_init(argc, argv, white_rabbit);
    else
        return (start_error("Incorrect content of arguments!", white_rabbit));

// Мониторинг
    i = 0;
    pthread_mutex_lock(white_rabbit->monitor);
    while(white_rabbit->flag != 2) // вечный цикл в главном потоке, чтобы он не завершал работы дочерних!
    {   // из-за detach главный поток main НЕ ЖДЁТ окончания работы функции test, это надо помнить!
        pthread_mutex_unlock(white_rabbit->monitor);

        if (i == white_rabbit->filo_count)
            i = 0;

        pthread_mutex_lock(&white_rabbit->status[i]);
        int time = what_current_time(*white_rabbit->t_start);

        if (time - white_rabbit->sages_arr[i]->current_life
               >= white_rabbit->how_long_life
               && white_rabbit->sages_arr[i]->how_much_eat != white_rabbit->how_much_need_eat) // или >= ?
        {
            pthread_mutex_lock(white_rabbit->mut_print);
            printf("time:%lld phil_num:%d died\n", what_current_time(*white_rabbit->t_start), white_rabbit->sages_arr[i]->id);
            break;
        }
        pthread_mutex_unlock(&white_rabbit->status[i]);
        i++;

        pthread_mutex_lock(white_rabbit->monitor);
    }
// Проблема явно с выходом потока после совершения определённого коли-
// чества трапез! Главный поток на этом моменте теряется.

// Чистим всё тут
    all_clean(white_rabbit);

    return (0);
}
