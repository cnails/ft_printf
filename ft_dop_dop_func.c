/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dop_dop_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:45:05 by cnails            #+#    #+#             */
/*   Updated: 2020/01/23 18:14:45 by cnails           ###   ########.fr       */
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

void		one_more_costil(t_printf *a, long long *l)
{
	char *d;
	char *b;

	d = ft_itoa(l[0]);
	b = ft_strjoin("+", d);
	collect(a, b, l[1] + 1);
	free(d);
	free(b);
}

void		col_with_sign(t_printf *a, long long *l, char *sign)
{
	char *s;
	char *d;
	char *p;
	char *b;

	p = ft_strset('0', a->space_2 - l[1]);
	s = ft_itoa(l[0] < 0 ? -l[0] : l[0]);
	d = ft_strjoin(p, s);
	b = ft_strjoin(sign, d);
	collect(a, b, a->space_2 + 1);
	free(s);
	free(p);
	free(b);
	free(d);
}
