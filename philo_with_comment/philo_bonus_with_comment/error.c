/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:07:26 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/07 19:07:52 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_error(char *a, t_baza *white_rabbit)
{
	if (white_rabbit)
		free(white_rabbit);
	printf("%s\n", a);
	return (0);
}

void	error_exit(t_baza *white_rabbit)
{
	white_rabbit->flag = 2;
	printf("Error\n");
	return ;
}
