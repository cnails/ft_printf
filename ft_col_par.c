/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_col_par.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2019/10/31 16:35:27 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_d(t_printf *a, int nb)
{
	int i;
	int f;
	int tmp;

	tmp = nb;
	i = 1;
	if ((f = (tmp < 0) ? 1 : 0))
		tmp *= -1;
	while ((tmp /= 10))
		i++;
	collect(a, ft_itoa(nb),i + f);
}

void	col_s(t_printf *a, char *str)
{
	collect(a, str, ft_strlen(str));
}

void	col_c(t_printf *a, char c)
{
	collect(a, &c, 1);
}

void	col_par(t_printf *a)
{
	if (*a->str == 'd' || *a->str == 'i' || *a->str == 'D' || *a->str == 'I')
		col_d(a, va_arg(a->va, int));
	if (*a->str == 's' || *a->str == 'S')
		col_s(a, va_arg(a->va, char *));
	if (*a->str == 'c' || *a->str == 'C')
		col_c(a, va_arg(a->va, int));
	if (*a->str == '%')
		collect(a, "%", 1);
}