/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabderus <rabderus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:56:40 by rabderus          #+#    #+#             */
/*   Updated: 2022/06/10 21:30:24 by rabderus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	count_leng(int n)
{
	int		lenght;

	lenght = 0;
	if (n < 0)
	{
		lenght++;
		n = n * (-1);
	}
	while (n / 10 != 0)
	{
		lenght++;
		n = n / 10;
	}
	lenght++;
	return (lenght);
}

char	*save_refund(int lenght, int i, int n, char *vozvrat)
{
	int	l;
	int	m;

	if (n < 0)
	{
		vozvrat[0] = '-';
		i++;
		lenght = (lenght - 1);
		n = n * (-1);
	}
	while (lenght > 0)
	{
		l = 1;
		m = 1;
		while (lenght > l)
		{
			m = m * 10;
			l++;
		}
		vozvrat[i] = (n / m) + '0';
		n = n % m;
		i++;
		lenght--;
	}
	return (vozvrat);
}

char	*ft_itoa(int n)
{
	int		lenght;
	int		i;
	char	*vozvrat;

	lenght = count_leng(n);
	i = 0;
	vozvrat = (char *)malloc((lenght + 1) * sizeof(char));
	if (!vozvrat)
		return (NULL);
	vozvrat[lenght] = '\0';
	if (n == -2147483648)
	{
		vozvrat[0] = '-';
		vozvrat[1] = 2 + '0';
		i = i + 2;
		lenght = (lenght - 2);
		n = 147483648;
	}
	return (save_refund(lenght, i, n, vozvrat));
}

char	*prisvaivaem(size_t	i, size_t j, char *s2, char *s3)
{
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = 0;
	return (s3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen (s1);
	j = ft_strlen (s2);
	s3 = (char *) malloc((i + j + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	prisvaivaem(i, j, s2, s3);
	return (s3);
}
