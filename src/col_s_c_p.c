/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col_s_c_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:41:35 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:41:36 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	col_s(t_printf *a, char *str)
{
	int u;

	a->space_2 = a->space_2 < 0 ? ft_strlen(str) : a->space_2;
	if (*a->str >= 0 && *a->str <= 9)
		dot_space(a);
	if (a->space && a->dot == 1 && !a->space_2)
	{
		collect(a, "", 0);
		return ;
	}
	if ((a->space_2 && a->dot == 1) || (a->space && a->dot == 1 && !a->space_2))
	{
		a->s = a->space_2 ? a->space_2 : a->space;
		if (a->space && a->dot == 1 && !a->space_2)
			a->space = 0;
		a->space_2 = 0;
	}
	if (str == NULL)
		str = "(null)";
	if ((int)ft_strlen(str) > a->s && a->dot == 1)
		u = a->s;
	else
		u = ft_strlen(str);
	collect(a, str, u);
}

void	dop_c(t_printf *a)
{
	char *tmp;

	write(a->fd, a->buf, a->len);
	free(a->buf);
	a->new_len += a->len + 1;
	a->len = 0;
	a->buf = NULL;
	if (a->space)
	{
		tmp = ft_strset(' ', a->space - 1);
		write(a->fd, tmp, a->space - 1);
		free(tmp);
		a->new_len += a->space - 1;
		a->space = 0;
	}
	write(a->fd, "\x00", 1);
}

void	col_c(t_printf *a, char c)
{
	if (a->space < 0 && c == '\x00')
	{
		write(a->fd, a->buf, a->len);
		a->buf = 0;
		a->buf = NULL;
		write(a->fd, "\x00", 1);
		a->new_len += a->len + 1;
		a->len = 0;
		a->space++;
		collect(a, "", 0);
	}
	else if (c == '\x00' && a->align)
	{
		write(a->fd, "\x00", 1);
		a->space++;
		collect(a, "", 0);
	}
	else if (c == '\x00')
		dop_c(a);
	else
		collect(a, &c, 1);
}

void	col_p(t_printf *a, void *str, char c)
{
	char	*s;
	char	*tmp;

	s = ret_s(a, str, c);
	if (a->dot && a->space_2 && a->space)
	{
		dop_p(a, s);
	}
	else if (a->dot)
	{
		a->space = 0;
		collect(a, "0x", 2);
		a->dot = 2;
		a->space = a->space_2;
		collect(a, s, ft_strlen(s));
	}
	else
	{
		tmp = ft_strjoin("0x", s);
		collect(a, tmp, ft_strlen(s) + 2);
		free(tmp);
	}
	free(s);
}

void	col_o_one_more(t_printf *a, char *str)
{
	char *tmp;
	char *tmp_join;

	tmp = ft_strset('0', a->space_2 - ft_strlen(str));
	tmp_join = ft_strjoin(tmp, str);
	if (a->space && a->space_2)
		a->dot = 1;
	collect(a, tmp_join, a->space_2);
	free(tmp);
	free(tmp_join);
}
