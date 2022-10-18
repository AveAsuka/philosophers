#include "philo.h"

int start_error(char *a, t_baza *white_rabbit) 
{
    if(white_rabbit)
        free(white_rabbit);
    printf("%s\n", a);
    return(0);
}

void error_exit(t_baza *white_rabbit)
{
    white_rabbit->flag = 2;
    printf("Error\n");
    return ;
}