/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_x_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:27:35 by cnails            #+#    #+#             */
/*   Updated: 2020/01/29 16:43:41 by cnails           ###   ########.fr       */
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

char	*ret_us(t_printf *a, void *str, char c)
{
	if (a->h == 1)
		return (ft_itoa_base((unsigned short)str, 16, c == 'X' ? 'A' : 'a'));
	else if (a->h == 2)
		return (ft_itoa_base((unsigned char)str, 16, c == 'X' ? 'A' : 'a'));
	else if (a->l == 2)
		return (ft_itoa_base((unsigned long long)str, 16,\
			c == 'X' ? 'A' : 'a'));
	else if (a->l == 1)
		return (ft_itoa_base((long int)str, 16,\
			c == 'X' ? 'A' : 'a'));
	else
		return (ft_itoa_base((unsigned int)str, 16, c == 'X' ? 'A' : 'a'));
}

void	col_x_dop(t_printf *a, char *s, char c)
{
	char	*tmp;
	char	*tmp_set;
	char	*tmp_join;

	if (a->sharp && a->space > 2 && a->dot == 2 && a->sharp)
		a->space_2 = a->space - 2;
	if (a->space_2 > (int)ft_strlen(s))
	{
		tmp = ft_strset('0', a->space_2 - ft_strlen(s));
		tmp_set = ft_strjoin(tmp, s);
		tmp_join = ft_strjoin(c == 'x' ? "0x" : "0X", tmp_set);
		collect(a, tmp_join, a->space_2 + 2);
		free(tmp);
		free(tmp_set);
		free(tmp_join);
	}
	else
		collect(a, ft_strjoin(c == 'x' ? "0x" : "0X", s), ft_strlen(s) + 2);
}

void	cost(t_printf *a, char *s)
{
	int		zero;
	char	*tmp;
	char	*tmp_join;

	zero = 0;
	if (!ft_strcmp(s, "0") && (a->space_2 || a->dot == 1))
	{
		zero = 1;
		if (a->sharp && a->dot == 1 && a->space && !a->space_2)
			a->dot = 0;
	}
	if (a->space && !a->space_2 && a->sharp)
		a->space_2 = a->space;
	if (a->space_2 > (int)ft_strlen(s) && a->dot)
	{
		tmp = ft_strset('0', a->space_2 - ft_strlen(zero ? "" : s));
		tmp_join = ft_strjoin(tmp, zero ? "" : s);
		collect(a, tmp_join, a->space_2);
		free(tmp_join);
		free(tmp);
	}
	else
		collect(a, zero ? "" : s, ft_strlen(zero ? "" : s));
}

void	col_x(t_printf *a, void *str, char c)
{
	char	*s;

	s = ret_us(a, str, c);
	if (a->sharp == 1 && str != 0)
	{
		col_x_dop(a, s, c);
	}
	else
	{
		cost(a, s);
	}
	free(s);
	a->h = 0;
	a->l = 0;
}

void	col_p(t_printf *a, void *str, char c)
{
	char	*s;
	int		u;

	u = 0;
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
