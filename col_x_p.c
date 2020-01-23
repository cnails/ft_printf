/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/23 15:46:42 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ret_s(t_printf *a, void *str, char c)
{
	if (a->h == 1)
		return (ft_itoa_base((unsigned short)str, 16, c == 'X' ? 'A' : 'a'));
	else if (a->h == 2)
		return (ft_itoa_base((unsigned char)str, 16, c == 'X' ? 'A' : 'a'));
	else if (a->l == 2)
		return (ft_itoa_base((unsigned long long)str, 16,\
			c == 'X' ? 'A' : 'a'));
	else
		return (ft_itoa_base((long int)str, 16, c == 'X' ? 'A' : 'a'));
}

void	col_x_dop(t_printf *a, char *s, char c)
{
	if (a->sharp && a->space > 2 && a->dot == 2 && a->sharp)
		a->space_2 = a->space - 2;
	if (a->space_2 > ft_strlen(s))
		collect(a, ft_strjoin(c == 'x' ? "0x" : "0X",\
			ft_strjoin(ft_strset('0', a->space_2 - ft_strlen(s)),\
				s)), a->space_2 + 2);
	else
		collect(a, ft_strjoin(c == 'x' ? "0x" : "0X", s), ft_strlen(s) + 2);
}

void	col_x(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;

	s = ret_s(a, str, c);
	if (a->sharp == 1 && str != 0)
		col_x_dop(a, s, c);
	else
	{
		if (!ft_strcmp(s, "0") && (a->space_2 || a->dot == 1))
		{
			s = "";
			if (a->sharp && a->dot == 1 && a->space && !a->space_2)
				a->dot = 0;
		}
		if (a->space && !a->space_2 && a->sharp)
			a->space_2 = a->space;
		if (a->space_2 > ft_strlen(s) && a->dot)
			collect(a, ft_strjoin(ft_strset('0',\
				a->space_2 - ft_strlen(s)), s), a->space_2);
		else
			collect(a, s, ft_strlen(s));
	}
	a->h = 0;
	a->l = 0;
}

void	col_p(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;
	char	*tmp;

	s = ret_s(a, str, c);
	if (a->dot)
	{
		if (a->space)
		{
			u = a->space;
			a->space = 0;
		}
		collect(a, "0x", 2);
		a->space = u - 2;
		collect(a, s, ft_strlen(s));
	}
	else
		collect(a, ft_strjoin("0x", s), ft_strlen(s) + 2);
	free(s);
}
