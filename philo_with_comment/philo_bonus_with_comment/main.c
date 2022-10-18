/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:35:04 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 20:12:29 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Закрываем все процессы после смерти первого философа
void	kill_all_process(t_baza *white_rabbit)
{
	int i;

	i = 0;
	while (i < white_rabbit->filo_count)
	{
		kill(white_rabbit->pid[i], SIGKILL);
		i++;
	}
}

/* Суть бонусника в том, что мы меняем потоки на форки, но внутри каждого форка будет свой поток.
Меняем мъютексы на семафоры и не используем их вовсе.
После чекера инитим все необходимые семафоры, потом запускаем форки.
Абстракция с левыми и правыми вилками теперь меняется на абстракцию куча вилок.
Аюстракция с чётными и нечётными философами меняется две половины.

Суть сюжета:
1) У каждого процесса, включая главный будет два потока. Один отслеживает жизнедеятельность,
другой - количество трапез -- но тут не до конца уверен, надо проработать
*/
int	main(int argc, char **argv)
{
	t_baza	*white_rabbit;

// Через индивидуальный семафор никак не вариант, а через сторонний поток не хочется
// Тут без изменений
	white_rabbit = (t_baza *)malloc(sizeof(t_baza));
	if (!white_rabbit)
		error_exit (white_rabbit);
	white_rabbit->flag = 1;
	if (argc < 5 || argc > 6)
		return (start_error ("Incorrect number of arguments!", white_rabbit));
	
// Тут шаманим
	if (checker (argc, argv, white_rabbit) == 1)
		parent_child_struct_init (argc, argv, white_rabbit);
	else
		return (start_error("Incorrect content of arguments!", white_rabbit));
	
	if (white_rabbit->flag == 2)
	{
		all_clean(white_rabbit);
		return(0);
	}
	waitpid(-1, 0, 0);
	kill_all_process(white_rabbit);
	all_clean(white_rabbit);
	
	return (0);
}
