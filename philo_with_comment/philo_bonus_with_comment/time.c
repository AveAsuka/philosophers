/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:49:04 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 17:54:49 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	start;

	gettimeofday (&start, 0);
	return (start.tv_sec * 1000 + start.tv_usec / 1000);
}

long long int	what_current_time(struct timeval time)
{
	return (get_time() - (time.tv_sec * 1000) - (time.tv_usec / 1000));
}

long    ft_timestamp(struct timeval tv)
{
    struct timeval   ctv;
    struct timeval   dtv;
    gettimeofday(&ctv, NULL);
    dtv.tv_sec = ctv.tv_sec - tv.tv_sec;
    dtv.tv_usec = ctv.tv_usec - tv.tv_usec;
    if (dtv.tv_usec < 0)
    {
        dtv.tv_sec--;
        dtv.tv_usec += 1000000;
    }
    return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

void	my_usleep(int ms)
{
    struct timeval	ctv;
    long        dt;
    if (ms <= 0)
        return ;
    gettimeofday(&ctv, NULL);
    if (ms > 5)
        usleep((ms - 5) * 1000);
    dt = ft_timestamp(ctv);
    while (dt < ms)
    {
        usleep(100);
        dt = ft_timestamp(ctv);
    }
}
