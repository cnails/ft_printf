/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:41:47 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:41:48 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ret_s(t_printf *a, void *str, char c)
{
	if (a->dot && !a->space_2 && !((unsigned long long)str))
		return (ft_strnew(1));
	else if (a->h == 1)
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
		return (ft_uitoa_base((unsigned short)str, 16, c == 'X' ? 'A' : 'a'));
	else if (a->h == 2)
		return (ft_uitoa_base((unsigned char)str, 16, c == 'X' ? 'A' : 'a'));
	else if (a->l == 2)
		return (ft_uitoa_base((unsigned long long)str, 16,\
			c == 'X' ? 'A' : 'a'));
	else if (a->l == 1)
		return (ft_uitoa_base((long int)str, 16,\
			c == 'X' ? 'A' : 'a'));
	else
		return (ft_uitoa_base((unsigned int)str, 16, c == 'X' ? 'A' : 'a'));
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
	{
		tmp = ft_strjoin(c == 'x' ? "0x" : "0X", s);
		collect(a, tmp, ft_strlen(s) + 2);
		free(tmp);
	}
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
