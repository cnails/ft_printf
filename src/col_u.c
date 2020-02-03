/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:45:05 by cnails            #+#    #+#             */
/*   Updated: 2020/01/29 20:13:16 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long long	ret_unb(t_printf *a, void *nb)
{
	if (a->l == 1)
		return ((unsigned long)nb);
	else if (a->l == 2)
		return ((unsigned long long)nb);
	else if (a->h == 1)
		return ((unsigned short)nb);
	else if (a->h == 2)
		return ((unsigned char)nb);
	else
		return ((unsigned int)nb);
}

void		col_u_dop(t_printf *a, unsigned long long *f)
{
	char	*tmp;
	char	*new;
	char	*it;

	new = ft_strset('0', a->space_2 - f[0]);
	it = ft_itoa(f[1]);
	tmp = ft_strjoin(new, it);
	collect(a, tmp, a->space_2);
	free(new);
	free(it);
	free(tmp);
}

static int	ft_numlen(unsigned long long nb)
{
	if (nb >= 10)
		return (1 + ft_numlen(nb / 10));
	else
		return (1);
}

char		*ft_uitoa(unsigned long long n)
{
	char	*str;
	int		i;

	i = ft_numlen(n);
	if (!(str = (char *)malloc(sizeof(char) * (ft_numlen(n) + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i--] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

void		col_u(t_printf *a, void *nb)
{
	unsigned long long	f[4];
	char				*tmp;

	f[2] = ret_unb(a, nb);
	f[1] = f[2];
	f[0] = 1;
	while ((f[2] /= 10))
		f[0]++;
	f[0] = a->space && !a->space_2 && a->dot == 1 ? 0 : f[0];
	if (a->dot && !a->space)
	{
		a->dot = 2;
		a->space = a->space_2;
	}
	if (a->dot == 2 && !a->space_2 && !a->space)
		collect(a, "", 0);
	else if (a->dot && a->space && a->space_2 > (int)f[0])
		col_u_dop(a, f);
	else
	{
		tmp = ft_uitoa(f[1]);
		collect(a, tmp, f[0]);
		free(tmp);
	}
}
