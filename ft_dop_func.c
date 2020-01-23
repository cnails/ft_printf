/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dop_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/23 15:49:27 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	col_plus_min_sl(t_printf *a)
{
	if (*a->str == '-')
		a->align = 1;
	if (*a->str == '+')
		a->sign = 1;
	a->str++;
	if (*a->str == '-' || *a->str == '+' || *a->str == '\'')
		col_plus_min_sl(a);
}

void	col_dot(t_printf *a)
{
	if (*a->str == '#')
	{
		a->sharp = 1;
		a->str++;
	}
	if (*a->str == '.')
	{
		a->dot = 1;
		a->str++;
	}
	else if (*a->str == '0')
	{
		a->dot = 2;
		a->str++;
	}
	if (*a->str == '-')
	{
		a->dot = 0;
		col_plus_min_sl(a);
	}
	if (*a->str == '+')
		col_plus_min_sl(a);
	if (*a->str >= '0' && *a->str <= '9')
		dot_space(a);
}

void	col_hl(t_printf *a)
{
	if (*a->str == 'h')
	{
		if (a->h == 1)
			a->h = 2;
		else
			a->h = 1;
	}
	if (*a->str == 'l')
	{
		if (a->l == 1)
			a->l = 2;
		else
			a->l = 1;
	}
	a->str++;
	if (*a->str == 'h' || *a->str == 'l')
		col_hl(a);
}
