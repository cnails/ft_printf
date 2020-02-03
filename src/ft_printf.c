/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmetallo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:42:48 by dmetallo          #+#    #+#             */
/*   Updated: 2020/01/30 16:42:50 by dmetallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		dop_p(t_printf *a, char *s)
{
	char *new;
	char *tmp;
	char *join;

	if (a->space_2 > a->space)
	{
		new = ft_strset('0', a->space_2 - ft_strlen(s));
		tmp = ft_strjoin(new, s);
		join = ft_strjoin("0x", tmp);
		collect(a, join, ft_strlen(s) + 2 + ft_strlen(new));
		free(new);
		free(tmp);
		free(join);
	}
	else
	{
		join = ft_strjoin("0x", s);
		collect(a, join, ft_strlen(s) + 2);
		free(join);
	}
}

void		col_space(t_printf *a, size_t len)
{
	char *tmp;
	char *p;

	a->space *= (a->space < 0) ? -1 : 1;
	if (a->dot == 2 && !a->align && !a->sharp)
	{
		p = ft_strset('0', a->space - len);
		a->dot = 0;
	}
	else
		p = ft_strset(' ', a->space - len);
	tmp = ft_strjoin(a->buf, p);
	free(a->buf);
	free(p);
	a->buf = tmp;
	a->len += a->space - len;
}

void		collect(t_printf *a, char *str, size_t len)
{
	char *tmp;
	char *new;

	if (!a->buf)
		a->buf = ft_strnew(1);
	if (a->space > (int)len && (!a->align || a->dot) && a->space > 0)
		col_space(a, len);
	tmp = ft_strsub(str, 0, len);
	new = ft_strjoin(a->buf, tmp);
	free(tmp);
	tmp = new;
	free(a->buf);
	a->buf = tmp;
	a->len += len;
	if (a->space < 0 && -a->space > (int)len)
		col_space(a, len);
	a->dot = (a->one_s ? a->dot : 0);
	a->sharp = 0;
	a->space = 0;
	a->h = 0;
	a->l = 0;
	a->big_l = 0;
}

void		a_init(const char *str, t_printf *a)
{
	a->fd = 1;
	a->n = 0;
	a->space = 0;
	a->new_len = 0;
	a->str = (char *)str;
}

int			ft_printf(const char *str, ...)
{
	t_printf	a;

	ft_bzero(&a, sizeof(a));
	va_start(a.va, str);
	a_init(str, &a);
	while (*a.str)
	{
		if (*a.str == '%')
		{
			a.str++;
			while ((*a.str) == ' ')
				a.str++;
			if (!(*a.str))
				break ;
			col_par(&a);
		}
		else
			collect(&a, a.str, 1);
		a.str++;
	}
	write(a.fd, a.buf, a.len);
	show(&a);
	free(a.buf);
	va_end(a.va);
	return (a.len + a.new_len);
}
