/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_u.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 18:45:05 by cnails            #+#    #+#             */
/*   Updated: 2020/01/28 20:56:32 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void		col_u(t_printf *a, void *nb)
{
	unsigned long long	f[4];

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
		collect(a, ft_strjoin(ft_strset('0', a->space_2 - f[0]),\
			ft_itoa(f[1])), a->space_2);
	else
		collect(a, ft_itoa(f[1]), f[0]);
}
