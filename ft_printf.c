/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnails <cnails@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:18:53 by cnails            #+#    #+#             */
/*   Updated: 2019/10/25 11:25:01 by cnails           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	collect(t_printf *a, char *str, size_t len)
{
	char *tmp;

	tmp = a->buf;
	a->len += len;
	a->buf = ft_memalloc(a->len);
	a->buf = tmp;
	a->buf = ft_strncpy(a->buf, str, len);
	// printf("%s\n", tmp);
	// a->buf = ft_strcpy(a->buf, tmp);
	printf("%s\n", a->buf);
}

// void	col_d(t_printf *a, double d)
// {
// 	size_t len;

	
// }

void	col_s(t_printf *a, char *str)
{
	size_t len;

	// printf("%s\n", str);
	len = ft_strlen(str);
	collect(a, str, len);
}

void	col_c(t_printf *a, char c)
{
	char *str;

	str = ft_memalloc(2);
	str[0] = c;
	str[1] = '\0';
	collect(a, str, 1);
}

void	col_par(t_printf *a)
{
	// if (*a->str == 'd')
	// {
	// 	col_d(a, va_arg(a->va, double));
	// 	// printf("%d = it is double\n", va_arg(a->va, double));
	// 	// col_double(&a);
	// }
	// printf("%c", *a->str);
	if (*a->str == 's')
	{
		col_s(a, va_arg(a->va, char *));
		// printf("%s = it is str\n", va_arg(a->va, char *));
	}
	if (*a->str == 'c')
	{
		col_c(a, va_arg(a->va, int));
		// collect(a, va_arg(a->va, char), 1);
		// printf("%c = it is char\n", va_arg(a->va, char));
	}
}

int		ft_printf(const char *str, ...)
{
	t_printf	a;
	char lol[100];
	int i;

	i = 0;
	ft_bzero(&a, sizeof(a));
	a.fd = 1;
	a.str = (char *)str;
	va_start(a.va, str);
	while (*a.str)
	{
		// printf("%c", *a.str);
		if (*a.str == '%')
		{
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
	// printf("%s\n", va_arg(a.va, char *));
	// printf("%s\n", va_arg(a.va, char *));
	// while (a.str[i])
	// {
	// 	ft_putchar(a.str[i]);
	// 	i++;
	// }
	// printf("%d\n", ft_strlen(a.str));
	va_end(a.va);
	return (0);
}

int main()
{
	char *s_7 = "seven";
	ft_printf("hello");//\n", "it is");
	// printf("hello %s", "it is");
	// printf("%s %c %d", 7, "hello", 59);
	// ft_printf("hello%d %s ", "six", s_7, "nice");
	return (0);
}
