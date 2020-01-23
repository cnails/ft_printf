/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:45:05 by cnails            #+#    #+#             */
/*   Updated: 2020/01/23 15:28:19 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		collect_space(t_printf *a)
{
	int tmp_space;
	int tmp_space_2;

	tmp_space = a->space;
	tmp_space_2 = a->space_2;
	a->space = 0;
	a->space_2 = 0;
	collect(a, " ", 1);
	a->one_s = 0;
	if (tmp_space && a->align)
		a->space = tmp_space + 1;
	else
		a->space = tmp_space - ((a->dot == 2) ? 1 : 0);
	a->space_2 = (tmp_space_2 && a->align && a->dot == 2) ?\
		tmp_space_2 + 1 : tmp_space_2;
}

long long	ret_nb(t_printf *a, void *nb)
{
	if (a->l == 1)
		return ((long)nb);
	else if (a->l == 2)
		return ((long long)nb);
	else if (a->h == 1)
		return ((short)nb);
	else if (a->h == 2)
		return ((char)nb);
	else
		return ((int)nb);
}

void		col_d_after_init(t_printf *a, long long *l)
{
	while ((l[3] /= 10))
		l[1]++;
	l[1] = a->space && !a->space_2 && a->dot == 1 ? 0 : l[1];
	if (a->dot == 2 && !a->space_2 && a->space && (l[0] < 0 || a->sign))
		a->space_2 = a->space - 1;
	if (a->sign)
		l[4] = l[0] >= 0 ? '+' : '-';
	if (a->one_s == 1 && !a->sign && l[0] >= 0 &&\
		(a->space <= l[1] || a->dot == 2))
		collect_space(a);
	if (a->dot && !a->space_2 && !a->space)
		a->sign ? collect(a, "+", 1) : collect(a, "", 0);
	else if (a->dot && l[0] < 0 && a->space_2 >= l[1])
		collect(a, ft_strjoin("-", ft_strjoin(ft_strset('0',\
			a->space_2 - l[1]), ft_itoa(-l[0]))), a->space_2 + 1);
	else if (a->dot && a->space_2 >= l[1] && l[4] == '+')
		collect(a, ft_strjoin("+", ft_strjoin(ft_strset('0',\
			a->space_2 - l[1]), ft_itoa(l[0]))), a->space_2 + 1);
	else if (a->dot && a->space_2 > l[1])
		collect(a, ft_strjoin(ft_strset('0', a->space_2 - l[1]),\
			ft_itoa(l[0])), a->space_2);
	else if (a->sign && l[0] >= 0 && l[4] != '-')
		collect(a, ft_strjoin("+", ft_itoa(l[0])), l[1] + 1);
	else
		collect(a, ft_itoa(l[0]), l[1] + (l[0] < 0 ? 1 : 0));
}

void		col_d(t_printf *a, void *nb)
{
	long long	l[5];

	l[3] = ret_nb(a, nb);
	l[0] = l[3];
	l[1] = 1;
	l[4] = '-';
	col_d_after_init(a, l);
}
