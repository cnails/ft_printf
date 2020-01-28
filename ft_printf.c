/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:18:53 by cnails            #+#    #+#             */
/*   Updated: 2020/01/28 21:23:24 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		col_space(t_printf *a, char *str, size_t len)
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
	if (a->space > len && (!a->align || a->dot) && a->space > 0)
		col_space(a, str, len);
	tmp = ft_strsub(str, 0, len);
	new = ft_strjoin(a->buf, tmp);
	free(tmp);
	tmp = new;
	free(a->buf);
	a->buf = tmp;
	a->len += len;
	if (a->space < 0 && -a->space > len)
		col_space(a, str, len);
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
	a->space = 0;
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
	write(1, a.buf, a.len);
	free(a.buf);
	va_end(a.va);
	return (a.len);
}

static int	len(int n)
{
	int i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

int			main()
{
	char	str[] = "0";
	// printf("%d\n", ft_strcmp(str, "a"));
	printf("%G\n", 888888888888);
	printf("%E\n", 80888888888888);
	// ft_printf("", )
//	ft_printf("%f", 1.0);
//	printf("\nthis %u number", -267);
	// printf("%d\n", -267);
	// printf("%ld\n", "s");
	// printf("{%+7u}\n", 0);
}
