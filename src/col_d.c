/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:39:37 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:39:49 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		col_dop(t_printf *a, long long *l)
{
	char *tmp;
	char *spaces;
	char *fuck;

	spaces = ft_strset('0', a->space_2 - l[1]);
	tmp = ft_itoa(l[0]);
	fuck = ft_strjoin(spaces, tmp);
	collect(a, fuck, a->space_2);
	free(tmp);
	free(fuck);
	free(spaces);
}

void		why(t_printf *a, long long *l)
{
	char	*norme;

	norme = ft_itoa(l[0]);
	collect(a, ft_strjoin("+", norme), l[1] + 1);
	free(norme);
}

void		last(t_printf *a, long long *l)
{
	char *c;

	if (l[0] == -9223372036854775807 - 1)
		c = ft_strdup("-9223372036854775808");
	else
		c = ft_itoa(l[0]);
	collect(a, c, l[1] + (l[0] < 0 ? 1 : 0));
	free(c);
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
		(a->space <= l[1] || a->dot == 2 || a->space_2 >= a->space))
		collect_space(a);
	if (a->dot == 1 && !a->space_2 && !a->space && l[0] == 0)
		a->sign ? collect(a, "+", 1) : collect(a, "", 0);
	else if (a->dot && l[0] < 0 && a->space_2 >= l[1])
		col_with_sign(a, l, "-");
	else if (a->dot && a->space_2 >= l[1] && l[4] == '+')
		col_with_sign(a, l, "+");
	else if (a->dot && a->space_2 > l[1])
		col_dop(a, l);
	else if (a->sign && l[0] >= 0 && l[4] != '-')
		one_more_costil(a, l);
	else
		last(a, l);
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
