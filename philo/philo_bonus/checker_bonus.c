/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:06:26 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 21:02:26 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	miss_tab(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

static long long	int
	schet_itog(const char *str, int znak, int i, t_baza *white_rabbit)
{
	long long int	itog;

	itog = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			itog = (itog * 10) + (str[i] - '0');
		else
			white_rabbit->flag = 0;
		i++;
	}
	itog = znak * itog;
	return (itog);
}

int	out(t_baza *white_rabbit)
{
	white_rabbit->flag = 0;
	return (0);
}

int	fatoi(const char *str, t_baza *white_rabbit)
{
	int				i;
	int				znak;
	long long int	itog;

	i = 0;
	znak = 1;
	if (!str)
		return (out(white_rabbit));
	i = miss_tab(str);
	if (str[i] == '-' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
	{
		znak = -1;
		i++;
	}
	else if (str[i] == '+' && (str[i + 1] >= '0' && str[i + 1] <= '9'))
		i++;
	else if ((str[i] >= '0' && str[i] <= '9'))
		;
	else
		return (out(white_rabbit));
	itog = schet_itog(str, znak, i, white_rabbit);
	if (-2147483648 <= itog && itog <= 2147483647)
		return ((int)itog);
	return (out(white_rabbit));
}

int	checker(int argc, char **argv, t_baza *white_rabbit)
{
	int	i;
	int	j;

	i = 1;
	while (i < 5)
	{
		j = fatoi(&*argv[i], white_rabbit);
		if ((white_rabbit->flag == 0) || (i == 1 && j <= 0) || (j < 0))
			return (0);
		i++;
	}
	if (argc == 6)
	{
		j = fatoi(&*argv[5], white_rabbit);
		if (white_rabbit->flag == 0 || j <= 0)
			return (0);
	}
	return (1);
}
